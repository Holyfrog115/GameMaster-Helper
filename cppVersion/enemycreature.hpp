#pragma once
#include "basecreature.hpp"
#include <iostream>
#include <string>

class EnemyCreature : public BaseCreature
{
private:
    double m_challengeRating;
    int m_xpReward;
    std::string m_type;

public:
    EnemyCreature(int str, int dex, int con, int intelligence, int wis, int cha, const std::string& name, int maxHp,
                  double challengeRating, int xpReward, const std::string& type);
    EnemyCreature();
    ~EnemyCreature() override;

    double GetChallengeRating() const
    {
        return m_challengeRating;
    }

    int GetXpReward() const
    {
        return m_xpReward;
    }

    std::string GetType() const
    {
        return m_type;
    }

    void SetChallengeRating(double challengeRating)
    {
        if (challengeRating < 0)
        {
            std::cout << "Ошибка. Уровень опасности существа не может быть < 0\n";
            return;
        }
        m_challengeRating = challengeRating;
    }

    void SetXpReward(int xpReward)
    {
        if (xpReward < 0)
        {
            std::cout << "Ошибка. Количество опыта за победу над существом не может быть < 0\n";
            return;
        }
        m_xpReward = xpReward;
    }

    void SetType(const std::string& type)
    {
        m_type = type;
    }

    void PrintInfo() const override;
    void TakeTurn() override;
};