cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall")

project(maze_runner)

add_executable(
    disjointset_tester
    disjointset.cpp
    disjointset_test.cpp
    timer.cpp
)

add_executable(
    maze_generator_test
    disjointset.cpp
    maze_generator_test.cpp
    maze_generator.cpp
)

add_executable(
    maze_runner_test
    maze_runner.cpp
    maze_runner_test.cpp
    maze.cpp
)