cmake_minimum_required(VERSION 4.1)
project(path)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(path
        path.cc
        path.hh
        path_example.cc
        unix_path.cc
        unix_path.hh
        windows_path.cc
        windows_path.hh)
