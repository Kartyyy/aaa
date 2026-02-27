cmake_minimum_required(VERSION 3.21.2)
project(exception)

add_executable(main main.cc player.cc invalid_argument.cc game.cc)
target_compile_options(main PRIVATE -Wall -Wextra -Werror -std=c++20 -pedantic
                                    -Wold-style-cast)
