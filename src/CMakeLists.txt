find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(Python3 COMPONENTS NumPy REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/libs)
add_executable(CPS main.cpp)
target_link_libraries(CPS Python3::NumPy)

target_compile_options(CPS PRIVATE
        -Wall
        -Werror
        -Wextra
        -Wno-unused-variable
        -Wno-maybe-uninitialized
        -Wnon-virtual-dtor
        -Wcast-align
        -Wunused
        -Wpedantic
        -Wmisleading-indentation
        -Wduplicated-cond
        -Wduplicated-branches
        -Wlogical-op
        -Wnull-dereference
        -Wuseless-cast
        -Wdouble-promotion
        #            -O3
        )