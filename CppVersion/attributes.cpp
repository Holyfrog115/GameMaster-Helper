#include "attributes.hpp"
#include "utility.hpp"
#include <iostream>
#include <string>

Attributes::Attributes(int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma)
{
    m_strength     = ValidAttribute(strength);
    m_dexterity    = ValidAttribute(dexterity);
    m_constitution = ValidAttribute(constitution);
    m_intelligence = ValidAttribute(intelligence);
    m_wisdom       = ValidAttribute(wisdom);
    m_charisma     = ValidAttribute(charisma);
    std::cout << "Объект класса Attributes был создан\n";
}

Attributes::~Attributes()
{
    std::cout << "Объект класса Attributes был удален\n";
}

// Get методы

int Attributes::GetStrength() const
{
    return m_strength;
}

int Attributes::GetDexterity() const
{
    return m_dexterity;
}

int Attributes::GetConstitution() const
{
    return m_constitution;
}

int Attributes::GetIntelligence() const
{
    return m_intelligence;
}

int Attributes::GetWisdom() const
{
    return m_wisdom;
}

int Attributes::GetCharisma() const
{
    return m_charisma;
}

// Set методы

void Attributes::SetStrength(int strength)
{
    m_strength = ValidAttribute(strength);
}

void Attributes::SetDexterity(int dexterity)
{
    m_dexterity = ValidAttribute(dexterity);
}

void Attributes::SetConstitution(int constitution)
{
    m_constitution = ValidAttribute(constitution);
}

void Attributes::SetIntelligence(int intelligence)
{
    m_intelligence = ValidAttribute(intelligence);
}

void Attributes::SetWisdom(int wisdom)
{
    m_wisdom = ValidAttribute(wisdom);
}

void Attributes::SetCharisma(int charisma)
{
    m_charisma = ValidAttribute(charisma);
}

int Attributes::CalculateModifier(std::string attribute) const
{
    std::string loweredString = LowerString(attribute);
    if (loweredString == "strength" || loweredString == "str")
    {
        return (m_strength - 10) / 2;
    }
    if (loweredString == "dexterity" || loweredString == "dex")
    {
        return (m_dexterity - 10) / 2;
    }
    if (loweredString == "constitution" || loweredString == "con")
    {
        return (m_constitution - 10) / 2;
    }
    if (loweredString == "intelligence" || loweredString == "int")
    {
        return (m_intelligence - 10) / 2;
    }
    if (loweredString == "wisdom" || loweredString == "wis")
    {
        return (m_wisdom - 10) / 2;
    }
    if (loweredString == "charisma" || loweredString == "cha")
    {
        return (m_charisma - 10) / 2;
    }

    return 0;
}

int Attributes::CalculateCarryingCapacity() const
{
    return m_strength * 15;
}

int Attributes::ValidAttribute(int attribute) const
{
    if (attribute < 1)
    {
        return 1;
    }
    else if (attribute > 20)
    {
        return 20;
    }

    return attribute;
}