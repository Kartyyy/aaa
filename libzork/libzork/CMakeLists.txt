cmake_minimum_required(VERSION 3.21.2)

add_library(zork SHARED)

target_compile_features(zork PRIVATE cxx_std_20)
target_compile_options(zork PRIVATE
  -Wall -Wextra -Werror -pedantic -Wold-style-cast
)

target_link_options(zork PRIVATE "-Wl,--no-undefined")

target_include_directories(zork
  PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_sources(zork PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/exceptions.cc

  ${CMAKE_CURRENT_SOURCE_DIR}/src/runner/choice.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/runner/choice_impl.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/runner/html.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/runner/html_impl.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/runner/interactive.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/runner/runner.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/runner/smart.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/runner/smart_impl.cc

  ${CMAKE_CURRENT_SOURCE_DIR}/src/store/store.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/store/store_impl.cc

  ${CMAKE_CURRENT_SOURCE_DIR}/src/story/choice.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/story/node.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/story/node_impl.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/story/story.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/story/story_impl.cc

  ${CMAKE_CURRENT_SOURCE_DIR}/src/vars/action.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vars/action_impl.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vars/condition.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vars/condition_impl.cc
)

find_library(YAML_CPP_LIB yaml-cpp REQUIRED)
target_link_libraries(zork PRIVATE ${YAML_CPP_LIB})
