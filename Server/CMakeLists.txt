cmake_minimum_required(VERSION 3.19)
project(Server)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-pthread")

add_executable(Server main.cpp ServerSocket.cpp ServerSocket.h ListDiskNode.cpp ListDiskNode.h DiskNode.cpp DiskNode.h BytesConverter.cpp BytesConverter.h FileManager.cpp FileManager.h json.hpp Huffman.cpp Huffman.h HuffDict.cpp HuffDict.h StrChar.cpp StrChar.h)