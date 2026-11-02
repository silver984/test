cmake_minimum_required(VERSION 3.31.6)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(
  proj_test
  VERSION   1.0.0
  LANGUAGES C CXX
)

add_executable(bin_test)

set_target_properties(
  bin_test PROPERTIES
  OUTPUT_NAME "Test"
)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*)
target_sources(bin_test PRIVATE ${SOURCES})
target_include_directories(bin_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)