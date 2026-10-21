#include "playercharacter.hpp"
#include "attributes.hpp"
#include "utility.hpp"
#include <iostream>
#include <string>

PlayerCharacter::PlayerCharacter(int str, int dex, int con, int intelligence, int wis, int cha, const std::string& name,
                                 int level, int maxHp)
    : m_attributes(str, dex, con, intelligence, wis, cha)
    , m_name(name)
{
    if (level < 1)
    {
        std::cout << "Ошибка. Неположительный уровень персонажа. Установлен 1 уровень.\n";
        m_level = 1;
    }
    else if (level > 20)
    {
        std::cout << "Ошибка. Уровень персонажа > 20. Установлен 20 уровень.\n";
        m_level = 20;
    }
    else
    {
        m_level = level;
    }
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

    std::cout << "Объект класса Playercharacter был создан (" << m_name << ")\n";
}

PlayerCharacter::~PlayerCharacter()
{
    std::cout << "Объект класса Playercharacter был удален (" << m_name << ")\n";
}

// Get методы

std::string PlayerCharacter::GetName() const
{
    return m_name;
}

int PlayerCharacter::GetLevel() const
{
    return m_level;
}

int PlayerCharacter::GetCurrentHp() const
{
    return m_currentHp;
}

int PlayerCharacter::GetMaxHp() const
{
    return m_maxHp;
}

// Set методы

void PlayerCharacter::SetName(const std::string& name)
{
    m_name = name;
}

void PlayerCharacter::SetLevel(int level)
{
    if (level < 1)
    {
        std::cout << "Ошибка. Неположительный уровень персонажа.\n";
    }
    else if (level > 20)
    {
        std::cout << "Ошибка. Уровень персонажа > 20.\n";
    }
    else
    {
        m_level = level;
    }
}

void PlayerCharacter::SetCurrentHp(int currentHp)
{
    if (currentHp < 0)
    {
        std::cout << "Ошибка. Текущее здоровье не может быть отрицательным.\n";
    }
    else if (currentHp > m_maxHp)
    {
        std::cout << "Ошибка. Текущее здоровье не может быть больше максимального.\n";
    }
    else
    {
        m_currentHp = currentHp;
    }
}

void PlayerCharacter::SetMaxHp(int maxHp)
{
    if (maxHp < 1)
    {
        std::cout << "Ошибка. Неположительное значение максимального здоровья.\n";
    }
    else
    {
        m_maxHp = maxHp;
    }
}

void PlayerCharacter::TakeDamage(int damage)
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

void PlayerCharacter::Heal(int heal)
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

void PlayerCharacter::LevelUp()
{
    if (m_level < 20)
    {
        ++m_level;
        std::cout << "Уровень повышен. Текущий уровень: " << m_level << "\n";
    }
    else
    {
        std::cout << "Невозможно повысить уровень. Достигнут максимальный уровень (20).\n";
    }
}

int PlayerCharacter::RollInitiative() const
{
    return RollD20() + CalculateModifier("dex");
}

int PlayerCharacter::CalculateModifier(const std::string& attribute) const
{
    return m_attributes.CalculateModifier(attribute);
}

int PlayerCharacter::CalculateCarryingCapacity() const
{
    return m_attributes.CalculateCarryingCapacity();
}

void PlayerCharacter::PrintInfo() const
{
    std::cout << " - Имя персонажа: " << m_name << "\n";
    std::cout << " - Уровень: " << m_level << "\n";
    std::cout << " - Максимальное здоровье: " << m_maxHp << "\n";
    std::cout << " - Текущее здоровье: " << m_currentHp << "\n";
    std::cout << " - Характеристики:\n";
    m_attributes.PrintAttributes();
}