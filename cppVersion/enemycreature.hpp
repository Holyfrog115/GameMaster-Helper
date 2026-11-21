#pragma once
#include "basecreature.hpp"
#include "exceptions.hpp"
#include "ilootable.hpp"
#include <iostream>
#include <string>

class EnemyCreature : public BaseCreature, public Ilootable
{
private:
    double m_challengeRating;
    int m_xpReward;
    std::string m_type;

public:
    EnemyCreature(int str, int dex, int con, int intelligence, int wis, int cha, const std::string& name, int maxHp,
                  double challengeRating, int xpReward, const std::string& type);
    EnemyCreature();
    EnemyCreature(const EnemyCreature& other)                = default;
    EnemyCreature(EnemyCreature&& other) noexcept            = default;
    EnemyCreature& operator=(const EnemyCreature& other)     = default;
    EnemyCreature& operator=(EnemyCreature&& other) noexcept = default;
    ~EnemyCreature() noexcept override;

    std::unique_ptr<BaseCreature> Clone() const override;

    double GetChallengeRating() const
    {
        return m_challengeRating;
    }

    std::string GetType() const
    {
        return m_type;
    }

    void SetChallengeRating(double challengeRating)
    {
        if (challengeRating < 0)
        {
            throw InvalidStatException("Уровень опасности существа не может быть < 0.");
        }
        m_challengeRating = challengeRating;
    }

    void SetXpReward(int xpReward)
    {
        if (xpReward < 0)
        {
            throw InvalidStatException("Количество опыта за победу над существом не может быть < 0.");
        }
        m_xpReward = xpReward;
    }

    void SetType(const std::string& type)
    {
        m_type = type;
    }

    int GetXpReward() const override
    {
        return m_xpReward;
    }

    int GetGoldReward() const override
    {
        return static_cast<int>(m_challengeRating * 20);
    }

    std::string GetLootDescription() const override;

    void PrintInfo() const override;
    void TakeTurn() override;
};