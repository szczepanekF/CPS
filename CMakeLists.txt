cmake_minimum_required(VERSION 3.22.3)
project(CPS)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 23)
SET(CMAKE_C_COMPILER gcc)
SET(CMAKE_C_COMPILER_VERSION 8.1.0)
include(${CMAKE_SOURCE_DIR}/cmake/CMakeFunctions.cmake)
add_subdirectory(src)



