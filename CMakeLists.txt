cmake_minimum_required(VERSION 3.8)
project(computersystems_assignment_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        .gitattributes
        .gitignore
        filters.c
        filters.h
        main.c
        qsr.c
        qsr.h
        rscript_illustrations.R
        sensor.c
        sensor.h)

add_executable(computersystems_assignment_1 ${SOURCE_FILES})