#ifndef IRC_MESSAGE_H
#define IRC_MESSAGE_H

#include "../types.h"

class Message {

public:
    explicit Message(std::string raw_message);

    MessageType get_type();
    std::string get_content();

private:
    MessageType type;
    std::string content;

};


#endif //IRC_MESSAGE_H
