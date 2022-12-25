set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(day16_1 part1.cpp)
add_executable(day16_1_2 part1_2.cpp)
add_executable(day16_2 part2.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/testinput.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)