#pragma once
#include "basecreature.hpp"
#include <iostream>
#include <string>

class PlayerCharacter : public BaseCreature
{
private:
    int m_level;
    int m_successfulSavingThrows = 0;
    int m_failedSavingThrows     = 0;
    bool m_isDead                = false;
    std::string m_class;

public:
    PlayerCharacter(int str, int dex, int con, int intelligence, int wis, int cha, const std::string& name, int level,
                    int maxHp, const std::string& characterClass);
    PlayerCharacter();
    PlayerCharacter(const PlayerCharacter& other);
    PlayerCharacter(PlayerCharacter&& other) noexcept = default;
    PlayerCharacter& operator=(const PlayerCharacter& other);
    PlayerCharacter& operator=(PlayerCharacter&& other) noexcept = default;
    ~PlayerCharacter() override;

    std::unique_ptr<BaseCreature> Clone() const override;

    int GetLevel() const
    {
        return m_level;
    }
    bool IsDead() const
    {
        return m_isDead;
    }
    std::string GetClass() const
    {
        return m_class;
    }

    void SetLevel(int level)
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

    void SetClass(std::string characterClass)
    {
        m_class = characterClass;
    }

    void LevelUp();
    int CalculateCarryingCapacity() const;
    void PrintInfo() const override;
    void TakeTurn() override;
};