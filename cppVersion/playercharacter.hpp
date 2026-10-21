#pragma once
#include "attributes.hpp"
#include <string>

class PlayerCharacter
{
private:
    std::string m_name;
    int m_level;
    int m_currentHp;
    int m_maxHp;
    Attributes m_attributes;

public:
    PlayerCharacter(int str, int dex, int con, int intelligence, int wis, int cha, const std::string& name, int level,
                    int maxHp);
    ~PlayerCharacter();

    std::string GetName() const;
    int GetLevel() const;
    int GetCurrentHp() const;
    int GetMaxHp() const;
    int GetStrength() const;
    int GetDexterity() const;
    int GetConstitution() const;
    int GetIntelligence() const;
    int GetWisdom() const;
    int GetCharisma() const;

    void SetName(const std::string& name);
    void SetLevel(int level);
    void SetCurrentHp(int currentHp);
    void SetMaxHp(int maxHp);
    void SetStrength(int strength);
    void SetDexterity(int dexterity);
    void SetConstitution(int constitution);
    void SetIntelligence(int intelligence);
    void SetWisdom(int wisdom);
    void SetCharisma(int charisma);

    void TakeDamage(int damage);
    void Heal(int heal);
    void LevelUp();
    int RollInitiative() const;
    int CalculateModifier(const std::string& attribute) const;
    int CalculateCarryingCapacity() const;
    void PrintInfo() const;
};