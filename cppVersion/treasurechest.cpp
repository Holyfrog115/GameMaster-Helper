#include "treasurechest.hpp"
#include "exceptions.hpp"
#include <string>

TreasureChest::TreasureChest(const std::string& chestName, int gold, int xp)
    : m_chestName{chestName}
{
    {
        if (gold < 0)
        {
            throw InvalidStatException("Значение золота должно быть >= 0");
        }
        else
        {
            m_gold = gold;
        }
        if (xp < 0)
        {
            throw InvalidStatException("Значение опыта должно быть >= 0");
        }
        else
        {
            m_xp = xp;
        }
    }
}

std::string TreasureChest::GetLootDescription() const
{
    return "Награды из " + m_chestName + ":\n" + " - " + std::to_string(m_gold) + " золота\n" + " - " +
           std::to_string(m_xp) + " опыта\n";
}