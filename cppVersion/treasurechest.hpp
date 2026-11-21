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
    TreasureChest(const std::string& chestName, int gold, int xp);

    int GetXpReward() const override
    {
        return m_xp;
    }

    int GetGoldReward() const override
    {
        return m_gold;
    }

    std::string GetLootDescription() const override;
};