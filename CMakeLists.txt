cmake_minimum_required (VERSION 3.31)

project(mem)

set(CMAKE_C_STANDARD 11)

add_library(stack STATIC src/stack/stack.c)
target_include_directories(stack PUBLIC ${PROJECT_SOURCE_DIR}/inc)

add_executable(lru src/lru/main.c)
target_link_libraries(lru PRIVATE stack)
