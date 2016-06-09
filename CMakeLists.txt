cmake_minimum_required(VERSION 2.8)
project(image-similarity)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CImg/CImg.h pHash/pHash.cpp pHash/pHash.h cxxopts/cxxopts.hpp)
add_executable(image-similarity ${SOURCE_FILES})

