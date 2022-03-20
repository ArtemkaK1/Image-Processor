cmake_minimum_required(VERSION 3.20)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)

add_executable(image_processor image_processor.cpp image.cpp)
