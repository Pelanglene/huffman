cmake_minimum_required(VERSION 3.20)
project(archiver)

set(CMAKE_CXX_STANDARD 14)

add_executable(archiver
        main.cpp
        Putter.cpp
        headers/Putter.h
        headers/config.h
        Getter.cpp
        headers/Getter.h
        Coder.cpp
        headers/Coder.h
        HuffmanTree.cpp
        headers/HuffmanTree.h
        Parser.cpp
        headers/Parser.h
        Heap.cpp
        headers/Heap.h
        Decoder.cpp
        headers/Decoder.h)
