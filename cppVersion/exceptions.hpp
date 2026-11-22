#pragma once
#include <stdexcept>
#include <string>

class GameRuleException : public std::runtime_error
{
public:
    explicit GameRuleException(const std::string& message)
        : std::runtime_error{message}
    {
    }
};

class DeadCreatureException : public GameRuleException
{
public:
    explicit DeadCreatureException(const std::string& creatureName)
        : GameRuleException{"Невозможно применить действие: существо \"" + creatureName + "\" погибло."}
    {
    }
};

class InvalidStatException : public std::invalid_argument
{
public:
    explicit InvalidStatException(const std::string& message)
        : std::invalid_argument{message}
    {
    }
};