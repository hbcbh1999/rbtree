cmake_minimum_required(VERSION 2.8.12)
project(benchmark)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")

add_executable(benchmark-this-repository
    ../src/rbtree.h
    ../src/rbtree.c
    benchmark-this-repository.c
)
target_include_directories(benchmark-this-repository PRIVATE ../src)

add_executable(benchmark-linux-kernel-rbtree
    linux/rbtree.h
    linux/rbtree.c
    benchmark-linux-kernel-rbtree.c
)
target_include_directories(benchmark-linux-kernel-rbtree PUBLIC ./)
