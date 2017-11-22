cmake_minimum_required(VERSION 2.8)
enable_testing()
project(test)
include_directories(../src)
set(RBTREE_SOURCE
    ../src/rbtree.h
    ../src/rbtree.c
)
add_executable(test-insert-to-empty
    ${RBTREE_SOURCE}
    test-insert-to-empty.c
)
add_executable(test-insert-to-one
    ${RBTREE_SOURCE}
    test-insert-to-one.c
)
add_executable(test-insert-left-right-case
    ${RBTREE_SOURCE}
    test-insert-left-right-case.c
)
add_executable(test-insert-right-left-case
    ${RBTREE_SOURCE}
    test-insert-right-left-case.c
)
add_executable(test-insert-random-10000
    ${RBTREE_SOURCE}
    test-insert-random-10000.c
)
add_definitions(-DRBTREE_DEBUG)
add_test(test-insert-to-empty test-insert-to-empty)
add_test(test-insert-to-one test-insert-to-one)
add_test(test-insert-left-right-case test-insert-left-right-case)
add_test(test-insert-right-left-case test-insert-right-left-case)
add_test(test-insert-random-10000 test-insert-random-10000)
