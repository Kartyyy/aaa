cmake_minimum_required(VERSION 3.21.2)
project(zork LANGUAGES CXX)

add_subdirectory(libzork)

add_executable(zorkxplorer
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/options.cc
)

target_compile_features(zorkxplorer PRIVATE cxx_std_20)
target_compile_options(zorkxplorer PRIVATE
  -Wall -Wextra -Werror -pedantic -Wold-style-cast
)

target_include_directories(zorkxplorer PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/libzork/include
)

target_link_libraries(zorkxplorer PRIVATE zork)
