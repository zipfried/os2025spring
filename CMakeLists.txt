cmake_minimum_required (VERSION 3.31)

project(mem)

set(CMAKE_C_STANDARD 11)

add_library(stack STATIC src/stack/stack.c)
target_include_directories(stack PUBLIC ${PROJECT_SOURCE_DIR}/inc)

add_library(queue STATIC src/queue/queue.c)
target_include_directories(queue PUBLIC ${PROJECT_SOURCE_DIR}/inc)

add_executable(lru src/lru/main.c)
target_link_libraries(lru PRIVATE stack)

add_executable(fifo src/fifo/main.c)
target_link_libraries(fifo PRIVATE queue)

add_executable(malloc src/malloc/main.c)
