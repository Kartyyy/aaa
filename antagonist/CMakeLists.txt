cmake_minimum_required(VERSION 3.21.2)
project(ant LANGUAGES CXX)

add_subdirectory(libbeaver)

add_executable(beaver_run
    src/main.cc)

target_compile_features(beaver_run PRIVATE cxx_std_20)

target_compile_options(beaver_run PRIVATE
    -Wall -Wextra -Werror -pedantic -Wold-style-cast)

target_link_libraries(beaver_run PRIVATE beaver)
