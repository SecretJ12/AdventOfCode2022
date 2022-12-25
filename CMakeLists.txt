cmake_minimum_required(VERSION 3.23)
project(AoC)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    add_compile_options(-Wall -Wextra -Wconversion -pedantic -Wfatal-errors)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W3 /WX)

    # so the dll files are alongside the executables
    # and the windows loader is happy (no more error 0xc0000135)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

add_subdirectory("Helper")

add_subdirectory("Day01")
add_subdirectory("Day02")
add_subdirectory("Day03")
add_subdirectory("Day04")
add_subdirectory("Day05")
add_subdirectory("Day06")
add_subdirectory("Day07")
add_subdirectory("Day08")
add_subdirectory("Day09")
add_subdirectory("Day10")
add_subdirectory("Day11")
add_subdirectory("Day12")
add_subdirectory("Day13")
add_subdirectory("Day14")
add_subdirectory("Day15")
add_subdirectory("Day16")
