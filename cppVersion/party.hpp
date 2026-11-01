#pragma once
#include "playercharacter.hpp"
#include <memory>
#include <vector>

class Party
{
private:
    std::vector<std::shared_ptr<PlayerCharacter>> m_members;

public:
    Party();
    Party(std::shared_ptr<PlayerCharacter> character);
    Party(const std::vector<std::shared_ptr<PlayerCharacter>>& characters);
    ~Party();

    void AddCharacter(std::shared_ptr<PlayerCharacter> character);
    void AddCharacter(const std::vector<std::shared_ptr<PlayerCharacter>>& characters);
    void RemoveCharacter(size_t index);
    int CalcAvgLevel() const;
    void PrintParty() const;
};