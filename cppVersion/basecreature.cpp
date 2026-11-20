#include "basecreature.hpp"
#include "normaldp.hpp"
#include "utility.hpp"
#include <iostream>
#include <memory>

BaseCreature::BaseCreature(const std::string& name, int maxHp, int strength, int dexterity, int constitution,
                           int intelligence, int wisdom, int charisma)
    : m_name{name}
    , m_attributes{std::make_shared<Attributes>(strength, dexterity, constitution, intelligence, wisdom, charisma)}
    , m_damagePolicy{std::make_unique<NormalDamagePolicy>()}
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
    , m_damagePolicy{other.m_damagePolicy ? other.m_damagePolicy->Clone() : std::make_unique<NormalDamagePolicy>()}
    , m_attributes{other.m_attributes}
{
    ++s_creatureCount;
    std::cout << "BaseCreature(const BaseCreature& other) -> объект скопирован\n";
}

BaseCreature::BaseCreature(BaseCreature&& other) noexcept
    : m_name{std::move(other.m_name)}
    , m_maxHp{other.m_maxHp}
    , m_currentHp{other.m_currentHp}
    , m_damagePolicy{std::move(other.m_damagePolicy)}
    , m_attributes{std::move(other.m_attributes)}
{
    ++s_creatureCount;
    std::cout << "BaseCreature(BaseCreature&& other) -> объект перемещен\n";
}

BaseCreature& BaseCreature::operator=(const BaseCreature& other)
{
    if (this == &other)
    {
        return *this;
    }

    m_name         = other.m_name;
    m_currentHp    = other.m_currentHp;
    m_maxHp        = other.m_maxHp;
    m_damagePolicy = other.m_damagePolicy ? other.m_damagePolicy->Clone() : std::make_unique<NormalDamagePolicy>();
    m_attributes   = other.m_attributes;

    return *this;
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

    int actualDamage = m_damagePolicy->ModifyDamage(damage);
    std::cout << m_name << " получает " << actualDamage << " урона (базовый: " << damage
              << ", правило: " << m_damagePolicy->GetPolicyName() << ")\n";
    if (m_currentHp - actualDamage < 0)
    {
        m_currentHp = 0;
    }
    else
    {
        m_currentHp -= actualDamage;
    }
}

void BaseCreature::SetDamagePolicy(std::unique_ptr<IDamagePolicy> policy)
{
    if (policy != nullptr)
    {
        m_damagePolicy = std::move(policy);
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

void BaseCreature::PrintInfo() const
{
    std::string name = GetName();
    if (name.length() > 64)
    {
        name = name.substr(0, 64) + "...";
    }
    std::cout << " - Имя персонажа: " << name << "\n";
    std::cout << " - Максимальное здоровье: " << GetMaxHp() << "\n";
    std::cout << " - Текущее здоровье: " << GetCurrentHp() << "\n";
}

void BaseCreature::PrintCategory() const
{
    std::cout << "Категория: Базовое существо\n";
}