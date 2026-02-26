cmake_minimum_required(VERSION 3.21.2)

add_library(beaver SHARED
    src/beaver.cc
    src/beaver_impl.cc
)

target_include_directories(beaver
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/externals
)

target_compile_features(beaver PRIVATE cxx_std_20)

target_compile_options(beaver PRIVATE
    -Wall -Wextra -Werror -pedantic -Wold-style-cast
)

find_package(OpenCV REQUIRED)

target_link_libraries(beaver PRIVATE ${OpenCV_LIBS})
