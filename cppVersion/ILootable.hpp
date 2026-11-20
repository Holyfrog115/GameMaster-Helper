#pragma once
#include <string>

class Ilootable
{
public:
    virtual ~Ilootable() = default;

    virtual int GetXpReward() const                = 0;
    virtual int GetGoldReward() const              = 0;
    virtual std::string GetLootDescription() const = 0;
};