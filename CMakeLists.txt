cmake_minimum_required(VERSION 3.25)
project(clita C)

set(CMAKE_C_STANDARD 23)

add_executable(clita main.c lexer.c lexer.h util.c util.h)
