#include "party.hpp"
#include "exceptions.hpp"
#include "playercharacter.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

Party::Party()
{
    std::cout << "Объект класса Party был создан.\n";
}

Party::Party(std::shared_ptr<PlayerCharacter> character)
{
    AddCharacter(character);
    std::cout << "Объект класса Party был создан.\n";
}

Party::Party(const std::vector<std::shared_ptr<PlayerCharacter>>& characters)
{
    AddCharacter(characters);
    std::cout << "Объект класса Party был создан.\n";
}

Party::~Party() noexcept
{
    std::cout << "Объект класса Party был удален.\n";
}

void Party::AddCharacter(std::shared_ptr<PlayerCharacter> character)
{
    if (character != nullptr)
    {
        m_members.push_back(character);
    }
}

void Party::AddCharacter(const std::vector<std::shared_ptr<PlayerCharacter>>& characters)
{
    for (const std::shared_ptr<PlayerCharacter>& character : characters)
    {
        if (std::find(m_members.begin(), m_members.end(), character) == m_members.end())
        {
            AddCharacter(character);
        }
    }
}

void Party::RemoveCharacter(size_t index)
{
    if (index == 0 || (index - 1) >= m_members.size())
    {
        throw std::out_of_range("Некорректный номер участника группы.");
    }
    --index;
    m_members.erase(m_members.begin() + index);
}

void Party::RemoveCharacter(const PlayerCharacter* character)
{
    for (size_t i = 0; i < m_members.size(); ++i)
    {
        if (m_members[i].get() == character)
        {
            m_members.erase(m_members.begin() + i);
            return;
        }
    }
}

int Party::CalcAvgLevel() const
{
    if (m_members.empty())
    {
        return 0;
    }

    int totalLevel = 0;
    for (const std::shared_ptr<PlayerCharacter>& character : m_members)
    {
        totalLevel += character->GetLevel();
    }

    return totalLevel / m_members.size();
}

void Party::PrintParty() const
{
    std::cout << "Участники группы:\n";
    for (size_t i = 0; i < m_members.size(); ++i)
    {
        std::string name = m_members[i]->GetName();
        if (name.length() > 32)
        {
            name = name.substr(0, 32) + "...";
        }
        std::cout << i + 1 << ". " << name << "\n";
    }
}

bool Party::SearchCharacterByFullName(const std::string& name) const
{
    for (size_t i = 0; i < m_members.size(); ++i)
    {
        if (m_members[i]->GetName() == name)
        {
            return true;
        }
    }

    return false;
}

bool Party::SearchCharacter(const std::string& name) const
{
    for (size_t i = 0; i < m_members.size(); ++i)
    {
        if (m_members[i]->GetName().find(name) != std::string::npos)
        {
            return true;
        }
    }

    return false;
}

void Party::DistributeReward(const Ilootable& source) const
{
    std::cout << source.GetLootDescription();

    if (m_members.empty())
    {
        throw GameRuleException("Невозможно распределить награду: в группе нет участников.");
    }

    int xpPerMember   = source.GetXpReward() / static_cast<int>(m_members.size());
    int goldPerMember = source.GetGoldReward() / static_cast<int>(m_members.size());

    std::cout << "Каждому участнику: +" << xpPerMember << " опыта, " << goldPerMember << " золота.\n";
}

void Party::DistributeReward(const std::vector<const Ilootable*>& sources) const
{
    if (m_members.empty())
    {
        throw GameRuleException("Невозможно распределить награду: в группе нет участников.");
    }

    int totalXp   = 0;
    int totalGold = 0;
    for (const Ilootable* source : sources)
    {
        if (source != nullptr)
        {
            std::cout << source->GetLootDescription();
            totalXp += source->GetXpReward();
            totalGold += source->GetGoldReward();
        }
    }

    int xpPerMember   = totalXp / static_cast<int>(m_members.size());
    int goldPerMember = totalGold / static_cast<int>(m_members.size());

    std::cout << "Каждому участнику: +" << xpPerMember << " опыта, " << goldPerMember << " золота.\n";
}