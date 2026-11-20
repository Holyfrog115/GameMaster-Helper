#include "treasurechest.hpp"
#include <string>

std::string TreasureChest::GetLootDescription() const
{
    return "Награды из " + m_chestName + ":\n" + " - " + std::to_string(m_gold) + " золота\n" + " - " +
           std::to_string(m_xp) + " опыта\n";
}