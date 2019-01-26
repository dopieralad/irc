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
        src/server/server.h
        src/types.h
        src/read_message_in_progress/ReadMessageBuffer.cpp
        src/read_message_in_progress/ReadMessageBuffer.h
        src/written_message_in_progress/WrittenMessageBuffer.cpp
        src/written_message_in_progress/WrittenMessageBuffer.h
        src/message_handler/MessageHandler.cpp
        src/message_handler/MessageHandler.h
        src/message/Message.cpp
        src/message/Message.h
        src/storage/Storage.cpp
        src/storage/Storage.h
        src/channel/Channel.cpp
        src/channel/Channel.h src/utils/Utils.cpp src/utils/Utils.h)
