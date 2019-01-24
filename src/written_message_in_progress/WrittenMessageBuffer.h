#ifndef IRC_WRITTENMESSAGEINPROGRESS_H
#define IRC_WRITTENMESSAGEINPROGRESS_H


#include <string>

class WrittenMessageBuffer {

public:
    explicit WrittenMessageBuffer(std::string message);

    void write_some(int descriptor);

    bool has_been_written_completely();

private:
    int written_bytes = 0;
    std::string message;
};


#endif //IRC_WRITTENMESSAGEINPROGRESS_H
