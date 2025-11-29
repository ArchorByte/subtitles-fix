cmake_minimum_required(VERSION 3.10)
project(subtitles-fix)
set(CMAKE_CXX_STANDARD 17)

include_directories (
    ${CMAKE_SOURCE_DIR}/
    ${CMAKE_SOURCE_DIR}/src
)

file(GLOB MAIN main.cpp)
file(GLOB SRC src/*.cpp)

set(ALL_SOURCES
    ${MAIN}
    ${SRC}
)

add_executable(subfix ${ALL_SOURCES})
