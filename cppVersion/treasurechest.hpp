#pragma once
#include "ilootable.hpp"
#include <string>

class TreasureChest : public Ilootable
{
private:
    std::string m_chestName;
    int m_gold;
    int m_xp;

public:
    TreasureChest(const std::string& chestName, int gold, int xp)
        : m_chestName{chestName}
    {
        if (gold < 0)
        {
            m_gold = 0;
        }
        else
        {
            m_gold = gold;
        }
        if (xp < 0)
        {
            m_xp = 0;
        }
        else
        {
            m_xp = xp;
        }
    }

    int GetXpReward() const override
    {
        return m_xp;
    }

    int GetGoldReward() const override
    {
        return m_gold;
    }

    std::string GetLootDescription() const override {}
};