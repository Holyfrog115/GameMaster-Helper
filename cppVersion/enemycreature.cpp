#include "enemycreature.hpp"
#include "attributes.hpp"
#include <iostream>
#include <string>

EnemyCreature::EnemyCreature(int str, int dex, int con, int intelligence, int wis, int cha, const std::string& name,
                             int maxHp, double challengeRating, int xpReward, const std::string& type)
    : BaseCreature{name, maxHp, str, dex, con, intelligence, wis, cha}
    , m_type{type}
{
    if (challengeRating < 0)
    {
        std::cout << "Ошибка. Уровень опасности существа не может быть < 0. Установлено значение 0.\n";
        m_challengeRating = 0;
    }
    else
    {
        m_challengeRating = challengeRating;
    }

    if (xpReward < 0)
    {
        std::cout << "Ошибка. Количество опыта за победу над существом не может быть < 0. Установлено значение 0.\n";
        m_xpReward = 0;
    }
    else
    {
        m_xpReward = xpReward;
    }

    std::cout << "EnemyCreature() -> Объект создан\n";
}

EnemyCreature::EnemyCreature()
    : EnemyCreature(10, 10, 10, 10, 10, 10, "", 1, 0, 0, "")
{
}

EnemyCreature::~EnemyCreature()
{
    std::cout << "~EnemyCreature() -> Объект уничтожен.\n";
}

std::unique_ptr<BaseCreature> EnemyCreature::Clone() const
{
    return std::make_unique<EnemyCreature>(*this);
}

void EnemyCreature::PrintInfo() const
{
    std::string name = GetName();
    if (name.length() > 64)
    {
        name = name.substr(0, 64) + "...";
    }
    std::cout << " - Существо: " << name << "\n";
    std::cout << " - Максимальное здоровье: " << GetMaxHp() << "\n";
    std::cout << " - Текущее здоровье: " << GetCurrentHp() << "\n";
    std::cout << " - Тип существа: " << m_type << "\n";
    std::cout << " - Уровень опасности: " << m_challengeRating << "\n";
    std::cout << " - Награда за победу: " << m_xpReward << " опыта\n";
    std::cout << " - Характеристики:\n";
    m_attributes->PrintAttributes();
}

void EnemyCreature::TakeTurn()
{
    if (GetCurrentHp() == 0)
    {
        std::cout << GetName() << " погиб.\n";
        // Награда за победу над врагом добавляется в результаты битвы в трекере ходов
        // После чего существо удаляется из трекера
    }
    else
    {
        // Совершает ход
        std::cout << GetName() << " совершает атаку.\n";
    }
}