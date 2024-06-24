cmake_minimum_required(VERSION 3.28)
project(MovieGraph_C C)

set(CMAKE_C_STANDARD 11)

add_executable(MovieGraph_C src/main.c
        include/movies.h
        include/structures.h
        src/movies.c
        src/actors.c
        include/neighbors.h
        src/neighbors.c)
