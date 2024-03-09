function(add_app APP_NAME)
    add_executable(${APP_NAME} ${ARGN})
    get_property(PROJECT_LIBS GLOBAL PROPERTY PROJECT_LIBS_TARGETS)
    target_link_libraries(${APP_NAME} PRIVATE "${PROJECT_LIBS}")
    set_link_options(${APP_NAME})
endfunction()

function(add_lib LIB_NAME)
    cmake_parse_arguments(ARGS "" "" "SOURCES;DEPENDS" ${ARGN})
    add_library(${LIB_NAME} ${ARGS_SOURCES})
    add_to_project_libs(${LIB_NAME})
    target_link_libraries(${LIB_NAME} PRIVATE "${ARGS_DEPENDS}")
    set_link_options(${LIB_NAME})
endfunction()

function(set_link_options TARGET_NAME)
    target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/libs)
#    target_link_libraries(${TARGET_NAME} PRIVATE Python3::NumPY)
    target_compile_options(${TARGET_NAME} PRIVATE
            -Wall
            -Wextra
#            -Werror
            -Wreturn-type
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
            #            -O3
            )
endfunction()

function(add_to_project_libs TARGET_NAME)
    get_property(PROJECT_LIBS GLOBAL PROPERTY PROJECT_LIBS_TARGETS)
    set_property(GLOBAL PROPERTY PROJECT_LIBS_TARGETS "${PROJECT_LIBS};${TARGET_NAME}")
endfunction()

macro(download_conan_cmake)
    if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan/conan.cmake")
        file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/develop2/conan_provider.cmake"
                "${CMAKE_BINARY_DIR}/conan/conan.cmake")
    endif ()


endmacro()