//
// Created by virzen on 24.01.19.
//

#ifndef IRC_MESSAGEINPROGRESS_H
#define IRC_MESSAGEINPROGRESS_H


#include <string>

class ReadMessageInProgress {

public:
    explicit ReadMessageInProgress(int desired_size);

    bool is_complete();

    std::string get_message();

    void append(char* chars, int length);

private:
    std::string message;
    int desired_size;
};


#endif //IRC_MESSAGEINPROGRESS_H
