cmake_minimum_required(VERSION 2.8.9)
project (main)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

file(GLOB SOURCES "src/*.c")
add_executable(main ${SOURCES})