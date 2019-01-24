cmake_minimum_required(VERSION 3.10)
project(IRC)

set(CMAKE_CXX_STANDARD 17)

add_executable(IRC_SERVER
        src/main.cpp
        src/error/error.cpp
        src/error/error.h
        src/connection_accepter/connection_accepter.cpp
        src/connection_accepter/connection_accepter.h
        src/multiplexer/multiplexer.cpp
        src/multiplexer/multiplexer.h
        src/server/server.cpp
        src/server/server.h src/types.h src/message_in_progress/MessageInProgress.cpp src/message_in_progress/MessageInProgress.h)
