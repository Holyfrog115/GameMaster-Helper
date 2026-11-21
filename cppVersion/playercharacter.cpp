#include "playercharacter.hpp"
#include "attributes.hpp"
#include "exceptions.hpp"
#include "party.hpp"
#include "utility.hpp"
#include <iostream>
#include <memory>
#include <string>

PlayerCharacter::PlayerCharacter(int str, int dex, int con, int intelligence, int wis, int cha, const std::string& name,
                                 int level, int maxHp, const std::string& characterClass)
    : BaseCreature{name, maxHp, str, dex, con, intelligence, wis, cha}
    , m_class{characterClass}
{
    if (level < 1 || level > 20)
    {
        throw InvalidStatException("Уровень персонажа должен быть от 1 до 20.");
    }
    else
    {
        m_level = level;
    }

    std::cout << "PlayerCharacter() -> Объект создан (" << GetName() << ")\n";
}

PlayerCharacter::PlayerCharacter()
    : PlayerCharacter(10, 10, 10, 10, 10, 10, "", 1, 1, "")
{
}

PlayerCharacter::PlayerCharacter(const PlayerCharacter& other)
    : BaseCreature(other)
{
    m_attributes             = std::make_shared<Attributes>(*other.m_attributes);
    m_class                  = other.m_class;
    m_successfulSavingThrows = other.m_successfulSavingThrows;
    m_failedSavingThrows     = other.m_failedSavingThrows;
    m_isDead                 = other.m_isDead;
    m_level                  = other.m_level;
    std::cout << "PlayerCharacter(const PlayerCharacter& other) -> объект скопирован\n";
}

PlayerCharacter& PlayerCharacter::operator=(const PlayerCharacter& other)
{
    if (this == &other)
    {
        return *this;
    }

    BaseCreature::operator=(other);
    m_attributes             = std::make_shared<Attributes>(*other.m_attributes);
    m_class                  = other.m_class;
    m_successfulSavingThrows = other.m_successfulSavingThrows;
    m_failedSavingThrows     = other.m_failedSavingThrows;
    m_isDead                 = other.m_isDead;
    m_level                  = other.m_level;

    return *this;
}

PlayerCharacter::~PlayerCharacter()
{
    std::cout << "~PlayerCharacter() -> Объект уничтожен (" << GetName() << ")\n";
}

std::unique_ptr<BaseCreature> PlayerCharacter::Clone() const
{
    return std::make_unique<PlayerCharacter>(*this);
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
        throw GameRuleException("Достигнут максимальный уровень персонажа (20).");
    }
}

int PlayerCharacter::CalculateCarryingCapacity() const
{
    return m_attributes->CalculateCarryingCapacity();
}

void PlayerCharacter::LeaveParty(Party& party)
{
    party.RemoveCharacter(this);
}

void PlayerCharacter::PrintInfo() const
{
    BaseCreature::PrintInfo();
    std::cout << " - Класс: " << m_class << "\n";
    std::cout << " - Уровень: " << m_level << "\n";
    std::cout << " - Характеристики:\n";
    m_attributes->PrintAttributes();
}

void PlayerCharacter::TakeTurn()
{
    if (m_isDead)
    {
        return;
    }
    if (GetCurrentHp() == 0)
    {
        if (RollD20() >= 10)
        {
            m_successfulSavingThrows++;
            std::cout << "Успешный спасбросок. (" << m_successfulSavingThrows << " из 3)\n";
        }
        else
        {
            m_failedSavingThrows++;
            std::cout << "Провальный спасбросок. (" << m_failedSavingThrows << " из 3)\n";
        }
        if (m_successfulSavingThrows == 3)
        {
            std::cout << GetName() << " стабилизировался и восстанавливает 1 HP\n";
            SetCurrentHp(1);
            return;
        }
        else if (m_failedSavingThrows == 3)
        {
            m_isDead = true;
            std::cout << GetName() << " погиб.\n";
            // Удаляется из трекера
            return;
        }
    }
    else
    {
        m_successfulSavingThrows = 0;
        m_failedSavingThrows     = 0;
        // Совершает ход
        std::cout << "Персонаж игрока " << GetName() << " совершает атаку.\n";
    }
}

void PlayerCharacter::PrintCategory() const
{
    std::cout << "Категория: Персонаж игрока (" << m_class << ")\n";
}

void PlayerCharacter::Heal(int heal)
{
    if (m_isDead)
    {
        throw DeadCreatureException(GetName());
    }
    BaseCreature::Heal(heal);
}