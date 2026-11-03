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

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CPM.cmake)

CPMAddPackage(
  NAME              lua_src
  GITHUB_REPOSITORY lua/lua
  GIT_TAG           v5.4.8
  GIT_SHALLOW       TRUE
  DOWNLOAD_ONLY     TRUE
)

file(GLOB LUA_SRC ${lua_src_SOURCE_DIR}/*.c)

list(
  REMOVE_ITEM LUA_SRC
  ${lua_src_SOURCE_DIR}/lua.c
  ${lua_src_SOURCE_DIR}/onelua.c
)

add_library(lua STATIC ${LUA_SRC})
target_include_directories(lua PUBLIC ${lua_src_SOURCE_DIR})

set(SOL2_BUILD_LUA OFF)
set(SOL2_LUA_VERSION "5.4.8")

CPMAddPackage(
  NAME              sol2
  GITHUB_REPOSITORY ThePhD/sol2
  GIT_TAG           v3.5.0
  GIT_SHALLOW       TRUE
)

set(POLYHOOK_BUILD_STATIC_RUNTIME OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/polyhook-v2)

target_link_libraries(
  bin_test PRIVATE
  lua
  sol2::sol2
  PolyHook_2
)

target_precompile_headers(bin_test PRIVATE <sol/sol.hpp>)