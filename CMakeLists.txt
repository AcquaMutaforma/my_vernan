cmake_minimum_required(VERSION 3.19)
project(oslab C)

set(CMAKE_C_STANDARD 99)

add_executable(bvernan main.c mycrypt.h mycrypt.c)