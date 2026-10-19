#pragma once
#include "playercharacter.hpp"
#include <vector>

class Party
{
private:
    std::vector<PlayerCharacter*> m_members;

public:
    Party(PlayerCharacter* character);
    Party(const std::vector<PlayerCharacter*>& characters);
    ~Party();

    void AddCharacter(PlayerCharacter* character);
    void AddCharacter(const std::vector<PlayerCharacter*>& characters);
    void RemoveCharacter(size_t index);
    int CalcAvgLevel() const;
};