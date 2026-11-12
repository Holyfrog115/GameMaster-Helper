#include "basecreature.hpp"
#include "utility.hpp"
#include <iostream>
#include <memory>

BaseCreature::BaseCreature(const std::string& name, int maxHp, int strength, int dexterity, int constitution,
                           int intelligence, int wisdom, int charisma)
    : m_name{name}
    , m_attributes{std::make_shared<Attributes>(strength, dexterity, constitution, intelligence, wisdom, charisma)}
{
    if (maxHp < 1)
    {
        std::cout << "Ошибка. Неположительное значение максимального здоровья. Установлено значение - 1\n";
        m_maxHp = 1;
    }
    else
    {
        m_maxHp = maxHp;
    }
    m_currentHp = m_maxHp;
    ++s_creatureCount;

    std::cout << "BaseCreature() -> Объект создан\n";
}

BaseCreature::BaseCreature()
    : BaseCreature{"", 1, 10, 10, 10, 10, 10, 10}
{
}

BaseCreature::BaseCreature(const BaseCreature& other)
    : m_name{other.GetName()}
    , m_currentHp{other.GetCurrentHp()}
    , m_maxHp{other.GetMaxHp()}
    , m_attributes{other.m_attributes}
{
    ++s_creatureCount;
    std::cout << "BaseCreature(const BaseCreature& other) -> объект скопирован\n";
}

BaseCreature::BaseCreature(BaseCreature&& other) noexcept
    : m_name{std::move(other.m_name)}
    , m_maxHp{other.m_maxHp}
    , m_currentHp{other.m_currentHp}
    , m_attributes{std::move(other.m_attributes)}
{
    ++s_creatureCount;
    std::cout << "BaseCreature(BaseCreature&& other) -> объект перемещен\n";
}

BaseCreature::~BaseCreature()
{
    --s_creatureCount;
    std::cout << "~BaseCreature() -> Объект уничтожен\n";
}

void BaseCreature::TakeDamage(int damage)
{
    if (damage < 0)
    {
        std::cout << "Ошибка. Значение урона должно быть положительным.\n";
        return;
    }
    if (m_currentHp - damage < 0)
    {
        m_currentHp = 0;
    }
    else
    {
        m_currentHp -= damage;
    }
}

void BaseCreature::Heal(int heal)
{
    if (heal < 0)
    {
        std::cout << "Ошибка. Значение исцеления должно быть положительным.\n";
        return;
    }
    if (m_currentHp + heal > m_maxHp)
    {
        m_currentHp = m_maxHp;
    }
    else
    {
        m_currentHp += heal;
    }
}

int BaseCreature::RollInitiative() const
{
    return RollD20() + CalculateModifier("dex");
}

int BaseCreature::CalculateModifier(const std::string& attribute) const
{
    return m_attributes->CalculateModifier(attribute);
}