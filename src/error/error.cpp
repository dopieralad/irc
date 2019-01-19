#include <iostream>
#include "error.h"

int Error::guard(int result, const char *message) {
    if (result == -1) {
        perror(message);
        exit(result);
    } else {
        return result;
    }
}
