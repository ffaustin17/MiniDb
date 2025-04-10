cmake_minimum_required(VERSION 3.14)
project(MiniDB)

set(CMAKE_CXX_STANDARD 17)

# add include directory
include_directories(include)

# source files
set(SOURCES
    src/main.cpp
    src/storage_engine.cpp
    src/pager.cpp
)

# add executable
add_executable(mini_db ${SOURCES})