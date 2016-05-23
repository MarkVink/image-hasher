cmake_minimum_required(VERSION 3.5)
project(image-hasher)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -stdlib=libc++")

set(SOURCE_FILES main.cpp CImg/CImg.h pHash/pHash.cpp pHash/pHash.h)
add_executable(image-hasher ${SOURCE_FILES})

