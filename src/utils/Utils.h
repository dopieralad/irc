#ifndef IRC_UTILS_H
#define IRC_UTILS_H

#include <string>
#include <vector>

class Utils {

public:
    static std::string join_vector(std::vector<int>);

    static int max(int, int);
    static unsigned long min(unsigned long, unsigned long);
};


#endif //IRC_UTILS_H
