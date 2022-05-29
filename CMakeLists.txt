cmake_minimum_required(VERSION 3.22)
project(Sharp C)

set(CMAKE_C_STANDARD 17)

add_executable(Sharp main.c stack.c stack.h math.c math.h)
