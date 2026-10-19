#include "utility.hpp"
#include <string>

std::string LowerString(const std::string& str)
{
    std::string loweredString;
    loweredString.reserve(str.length());
    for (char letter : str)
    {
        loweredString += std::tolower(letter);
    }

    return loweredString;
}