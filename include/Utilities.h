#ifndef UTILITIES_H
#define UTILITIES_H

#include <algorithm>
#include <string>
#include <cctype>

inline std::string makeLowercase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}

#endif // UTILITIES_H