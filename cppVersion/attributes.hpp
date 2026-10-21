#pragma once
#include <string>

class Attributes
{
private:
    int m_strength;
    int m_dexterity;
    int m_constitution;
    int m_intelligence;
    int m_wisdom;
    int m_charisma;

public:
    Attributes(int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma);
    ~Attributes();

    int GetStrength() const;
    int GetDexterity() const;
    int GetConstitution() const;
    int GetIntelligence() const;
    int GetWisdom() const;
    int GetCharisma() const;

    void SetStrength(int strength);
    void SetDexterity(int dexterity);
    void SetConstitution(int constitution);
    void SetIntelligence(int intelligence);
    void SetWisdom(int wisdom);
    void SetCharisma(int charisma);

    int CalculateModifier(std::string attribute) const;
    int CalculateCarryingCapacity() const;
    int ValidAttribute(int attribute) const;
    void PrintAttributes() const;
};