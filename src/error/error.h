#ifndef IRC_ERROR_H
#define IRC_ERROR_H


class Error {

public:
    static int guard(int result, const char *message);
};


#endif //IRC_ERROR_H
