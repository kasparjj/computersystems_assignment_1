cmake_minimum_required(VERSION 3.8)
project(cn)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        filters.c
        filters.h
        main.c
        qsr.c
        qsr.h
        sensor.c
        sensor.h)

add_executable(cn ${SOURCE_FILES})