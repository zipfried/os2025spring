cmake_minimum_required (VERSION 3.31)

project(mem)

set(CMAKE_C_STANDARD 11)

add_executable(lru src/lru/main.c src/lru/stack.c)
add_executable(fifo src/fifo/main.c)
