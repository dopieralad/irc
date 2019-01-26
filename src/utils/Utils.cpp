#include <algorithm>
#include "Utils.h"

std::string Utils::join_vector(std::vector<int> nums) {
    std::string out;

    for (int num : nums) {
        out += std::to_string(num) + ",";
    }

    out.resize(max(out.size() - 1, 0));

    return out;
}

int Utils::max(int a, int b) {
    return a > b ? a : b;
}
