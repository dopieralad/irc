//
// Created by virzen on 24.01.19.
//

#ifndef IRC_MESSAGEINPROGRESS_H
#define IRC_MESSAGEINPROGRESS_H


#include <string>

class ReadMessageBuffer {

public:
    explicit ReadMessageBuffer(int desired_size);

    bool has_been_read_completely();

    std::string get_message();

    void append(char* chars, int length);

    void read_some(int i);

private:
    std::string message;
    int desired_size;
};


#endif //IRC_MESSAGEINPROGRESS_H
