cmake_minimum_required(VERSION 3.12)

project(
        labwork3-Pzof1
        VERSION 1.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
add_executable(labwork3-Pzof1 main.cpp
        libraries/bmp/bmp.cpp
        libraries/bmp/bmp.h
        libraries/data-storage/data-storage.cpp
        libraries/data-storage/data-storage.h
        libraries/parser/parser.h
        libraries/parser/parser.cpp
        libraries/other-functions/other-functions.cpp
        libraries/other-functions/other-functions.h
)
add_subdirectory(libraries)
