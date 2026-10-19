#include "party.hpp"
#include "playercharacter.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

Party::Party(PlayerCharacter* character)
{
    AddCharacter(character);
    std::cout << "Объект класса Party был создан.\n";
}

Party::Party(const std::vector<PlayerCharacter*>& characters)
{
    AddCharacter(characters);
    std::cout << "Объект класса Party был создан.\n";
}

Party::~Party()
{
    std::cout << "Объект класса Party был удален.\n";
}

void Party::AddCharacter(PlayerCharacter* character)
{
    m_members.push_back(character);
}

void Party::AddCharacter(const std::vector<PlayerCharacter*>& characters)
{
    for (PlayerCharacter* character : characters)
    {
        if (std::find(m_members.begin(), m_members.end(), character) == m_members.end())
        {
            AddCharacter(character);
        }
    }
}

void Party::RemoveCharacter(size_t index)
{
    if (index == 0)
    {
        return;
    }
    --index;

    if (index < m_members.size())
    {
        m_members.erase(m_members.begin() + index);
    }
}

int Party::CalcAvgLevel() const
{
    if (m_members.empty())
    {
        return 0;
    }

    int totalLevel = 0;
    for (PlayerCharacter* character : m_members)
    {
        totalLevel += character->GetLevel();
    }

    return totalLevel / m_members.size();
}