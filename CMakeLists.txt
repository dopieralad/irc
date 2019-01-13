cmake_minimum_required(VERSION 3.10)
project(IRC)

set(CMAKE_CXX_STANDARD 17)

add_executable(IRC_SERVER
        src/main.cpp
        src/error/error.cpp
        src/error/error.h
        src/server/server.cpp
        src/server/server.h
        src/multiplexer/multiplexer.cpp
        src/multiplexer/multiplexer.h)
