#pragma once
#include "attributes.hpp"
#include "exceptions.hpp"
#include "idamagepolicy.hpp"
#include <memory>
#include <string>

class BaseCreature
{
private:
    std::string m_name;
    int m_currentHp;
    int m_maxHp;
    inline static int s_creatureCount = 0;
    std::unique_ptr<IDamagePolicy> m_damagePolicy;

protected:
    std::shared_ptr<Attributes> m_attributes;
    BaseCreature(const BaseCreature& other);
    BaseCreature(BaseCreature&& other) noexcept;
    BaseCreature& operator=(const BaseCreature& other);
    BaseCreature& operator=(BaseCreature&& other) noexcept = default;

public:
    BaseCreature(const std::string& name, int maxHp, int strength, int dexterity, int constitution, int intelligence,
                 int wisdom, int charisma);
    BaseCreature();
    virtual ~BaseCreature() noexcept;

    virtual std::unique_ptr<BaseCreature> Clone() const = 0;

    static int GetCreatureCount()
    {
        return s_creatureCount;
    }

    std::string GetName() const
    {
        return m_name;
    }
    int GetCurrentHp() const
    {
        return m_currentHp;
    }
    int GetMaxHp() const
    {
        return m_maxHp;
    }
    int GetStrength() const
    {
        return m_attributes->GetStrength();
    }
    int GetDexterity() const
    {
        return m_attributes->GetDexterity();
    }
    int GetConstitution() const
    {
        return m_attributes->GetConstitution();
    }
    int GetIntelligence() const
    {
        return m_attributes->GetIntelligence();
    }
    int GetWisdom() const
    {
        return m_attributes->GetWisdom();
    }
    int GetCharisma() const
    {
        return m_attributes->GetCharisma();
    }

    void SetName(std::string name)
    {
        m_name = name;
    }
    void SetCurrentHp(int hp)
    {
        if (hp < 0)
        {
            m_currentHp = 0;
        }
        else if (hp > m_maxHp)
        {
            m_currentHp = m_maxHp;
        }
        else
        {
            m_currentHp = hp;
        }
    }
    void SetMaxHp(int hp)
    {
        if (hp < 1)
        {
            throw InvalidStatException("Максимальное здоровье должно быть >= 1.");
        }
        else
        {
            m_maxHp = hp;
        }
        if (m_currentHp > m_maxHp)
        {
            m_currentHp = m_maxHp;
        }
    }
    void SetStrength(int strength)
    {
        m_attributes->SetStrength(strength);
    }
    void SetDexterity(int dexterity)
    {
        m_attributes->SetDexterity(dexterity);
    }
    void SetConstitution(int constitution)
    {
        m_attributes->SetConstitution(constitution);
    }
    void SetIntelligence(int intelligence)
    {
        m_attributes->SetIntelligence(intelligence);
    }
    void SetWisdom(int wisdom)
    {
        m_attributes->SetWisdom(wisdom);
    }
    void SetCharisma(int charisma)
    {
        m_attributes->SetCharisma(charisma);
    }

    void TakeDamage(int damage);
    virtual void Heal(int heal);
    int RollInitiative() const;
    int CalculateModifier(const std::string& attribute) const;
    virtual void PrintInfo() const;
    virtual void TakeTurn() = 0;
    void PrintCategory() const;
    void SetDamagePolicy(std::unique_ptr<IDamagePolicy> policy);
};
