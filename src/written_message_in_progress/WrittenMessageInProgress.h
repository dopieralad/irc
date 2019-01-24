#ifndef IRC_WRITTENMESSAGEINPROGRESS_H
#define IRC_WRITTENMESSAGEINPROGRESS_H


#include <string>

class WrittenMessageInProgress {

public:
    explicit WrittenMessageInProgress(std::string message);

    bool write_some(int descriptor);

private:
    int written_bytes = 0;
    std::string message;

    bool has_been_written_completely();
};


#endif //IRC_WRITTENMESSAGEINPROGRESS_H
