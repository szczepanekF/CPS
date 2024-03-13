cmake_minimum_required(VERSION 3.22.0)
include(${CMAKE_SOURCE_DIR}/cmake/CMakeFunctions.cmake)
download_conan_cmake()
set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES "${CMAKE_BINARY_DIR}/conan/conan.cmake")
project(CPS)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 23)
SET(CMAKE_C_COMPILER gcc)
SET(CMAKE_C_COMPILER_VERSION 11)

find_package(imgui)
find_package(glfw3)
find_package(glew)
find_package(implot)
#

add_subdirectory(src)
