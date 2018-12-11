cmake_minimum_required(VERSION 3.10)
project(IRC C)

set(CMAKE_C_STANDARD 11)

add_executable(IRC_SERVER server/main.c)
add_executable(IRC_CLIENT client/main.c)
