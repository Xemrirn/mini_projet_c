cmake_minimum_required(VERSION 4.0)
project(mini_projet C)

set(CMAKE_C_STANDARD 11)

include_directories(..)

add_executable(mini_projet
        main.c
        main.h
        fractale.c
        fractale.h
        utils.c
        utils.h)
