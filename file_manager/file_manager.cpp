//
// Created by Artemiy Kirillov on 3/14/22.
//

#include "file_manager.h"

BMP::BMP(const char *file_name) {
    read(file_name);
}

void BMP::read(const char *file_name) {
    std::ifstream inp{ file_name, std::ios_base::binary };
    if (inp) {
        inp.read((char*)&file_header, sizeof(file_header));
        if(file_header.file_type != 0x4D42) {
            throw std::runtime_error("Error! Unrecognized file format.");
        }
        inp.read((char*)&bmp_info_header, sizeof(bmp_info_header));
        // The BMPColorHeader is used only for transparent images
        if(bmp_info_header.bit_count == 32) {
            inp.read((char*)&bmp_color_header, sizeof(bmp_color_header));
            // Check if the pixel data is stored as BGRA and if the color space type is sRGB
            check_color_header(bmp_color_header);
        }
        // Jump to the pixel data location
        inp.seekg(file_header.offset_data, inp.beg);

        // Adjust the header fields for output.
        // Some editors will put extra info in the image file, we only save the headers and the data.
        if(bmp_info_header.bit_count == 32) {
            bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
            file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
        } else {
            bmp_info_header.size = sizeof(BMPInfoHeader);
            file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
        }
        file_header.file_size = file_header.offset_data;

        if (bmp_info_header.height < 0) {
            throw std::runtime_error("The program can treat only BMP images with the origin in the bottom left corner!");
        }

        data.resize(bmp_info_header.width * bmp_info_header.height * bmp_info_header.bit_count / 8);

        // Here we check if we need to take into account row padding
        if (bmp_info_header.width % 4 == 0) {
            inp.read((char*)data.data(), data.size());
            file_header.file_size += data.size();
        } else {
            row_stride = bmp_info_header.width * bmp_info_header.bit_count / 8;
            uint32_t new_stride = make_stride_aligned(4);
            std::vector<uint8_t> padding_row(new_stride - row_stride);

            for (int y = 0; y < bmp_info_header.height; ++y) {
                inp.read((char*)(data.data() + row_stride * y), row_stride);
                inp.read((char*)padding_row.data(), padding_row.size());
            }
            file_header.file_size += data.size() + bmp_info_header.height * padding_row.size();
        }
    } else {
        throw std::runtime_error("Unable to open the input image file.");
    }
}

void BMP::write(const char *file_name) {
    std::ofstream of{ file_name, std::ios_base::binary };
    if (of) {
        if (bmp_info_header.bit_count == 32) {
            write_headers_and_data(of);
        } else if (bmp_info_header.bit_count == 24) {
            if (bmp_info_header.width % 4 == 0) {
                write_headers_and_data(of);
            } else {
                uint32_t new_stride = make_stride_aligned(4);
                std::vector<uint8_t> padding_row(new_stride - row_stride);
                write_headers(of);
                for (int y = 0; y < bmp_info_header.height; ++y) {
                    of.write((const char*)(data.data() + row_stride * y), row_stride);
                    of.write((const char*)padding_row.data(), padding_row.size());
                }
            }
        } else {
            throw std::runtime_error("The program can treat only 24 or 32 bits per pixel BMP files");
        }
    } else {
        throw std::runtime_error("Unable to open the output image file.");
    }
}
