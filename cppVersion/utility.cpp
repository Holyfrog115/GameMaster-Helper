#include "utility.hpp"
#include <random>
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

int RollD20()
{
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_int_distribution<int> d20(1, 20);

    return d20(generator);
}