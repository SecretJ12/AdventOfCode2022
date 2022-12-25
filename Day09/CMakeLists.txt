

add_executable(day09_1 part1.cpp)
add_executable(day09_2 part2.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/testinput.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/testinput2.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)