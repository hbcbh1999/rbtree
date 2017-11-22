cmake_minimum_required(VERSION 2.8)
project(example)
set(targetName example)
include_directories(../src)
add_executable(${targetName}
    ../src/rbtree.h
    ../src/rbtree.c
    example.c
)
add_definitions(-DRBTREE_DEBUG)
