cmake_minimum_required(VERSION 3.10)
project(IRC)

set(CMAKE_CXX_STANDARD 17)

add_executable(IRC_SERVER
        server/main.cpp
        common/error.cpp
        common/error.h
        server/server/server.cpp
        server/server/server.h
        server/multiplexer/multiplexer.cpp
        server/multiplexer/multiplexer.h)

add_executable(IRC_CLIENT
        client/main.cpp)

target_link_libraries(IRC_CLIENT ws2_32)
