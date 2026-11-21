#include "attributes.hpp"
#include "enemycreature.hpp"
#include "exceptions.hpp"
#include "idamagepolicy.hpp"
#include "ilootable.hpp"
#include "party.hpp"
#include "playercharacter.hpp"
#include "resistancedp.hpp"
#include "treasurechest.hpp"
#include "vulnerabilitydp.hpp"
#include <iostream>
#include <memory>
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif

int main()
{
#if defined(_WIN32) || defined(_WIN64)
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif
    // Композиция
    std::cout << "--- КОМПОЗИЦИЯ: ---\n";
    std::shared_ptr<PlayerCharacter> character1 = std::make_shared<PlayerCharacter>(
        10, 10, 10, 14, 12, 15,
        "РобославРобославРобославРобославРобославРобославРобославРобославРобославРобославРобослав", 5, 65, "Воин");
    std::shared_ptr<PlayerCharacter> character2 =
        std::make_shared<PlayerCharacter>(16, 10, 14, 8, 8, 10, "Иван-Джон-Пьер", 6, 105, "Варвар");
    std::shared_ptr<PlayerCharacter>& character2ref = character2;
    std::shared_ptr<PlayerCharacter> character3 =
        std::make_shared<PlayerCharacter>(8, 8, 8, 15, 15, 12, "Нилбог", 4, 32, "Жрец");

    // Вызов методов класса PlayerCharacter, которые используют методы класса Attributes
    std::cout << "Вызов методов класса PlayerCharacter:\n";
    character1->TakeDamage(1000);
    character1->Heal(10);
    character1->PrintInfo();
    std::cout << "Модификатор силы объекта character2: " << character2ref->CalculateModifier("str") << "\n";
    std::cout << "Бросок инициативы объекта character3: " << character3->RollInitiative() << "\n";

    std::cout << "При инициализации объекта класса PlayerCharacter создается объект класса Attributes:\n";
    {
        PlayerCharacter character4(8, 8, 8, 15, 15, 12, "Пример композиции", 4, 32, "");
        std::cout << "При удалении объекта класса Playercharacter удаляется и объект класса Attributes:\n";
    }

    // Агрегация
    std::cout << "\n--- АГРЕГАЦИЯ: ---\n";
    {
        Party party({character1, character2, character3});

        // Вызов методов класса Party, которые используют методы методы класса PlayerCharacter
        std::cout << "Вызов методов класса Party:\n";
        party.PrintParty();
        party.RemoveCharacter(3);
        std::cout << "После удаления персонажа:\n";
        party.PrintParty();
        std::cout << "Средний уровень группы: " << party.CalcAvgLevel() << "\n";
    }
    std::cout << "После удаления объекта Party персонажи все еще доступны. Имя объекта char1: " << character1->GetName()
              << "\n";

    // Статическая инициализация объекта
    std::cout << "\n--- СТАТИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТА ---\n";
    {
        static PlayerCharacter staticCharacter(10, 10, 10, 10, 10, 10, "Статик", 10, 10, "");
    }

    // Динамическая инициализация объекта
    std::cout << "\n--- ДИНАМИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТА ---\n";
    std::unique_ptr<PlayerCharacter> dynamicCharacter;
    {
        dynamicCharacter = std::make_unique<PlayerCharacter>(10, 10, 10, 10, 10, 10, "Динамическая память", 10, 10, "");
    }
    std::cout << "Имя: " << dynamicCharacter->GetName() << "\n";

    // Тест массивов
    std::cout << "\n--- ТЕСТ МАССИВОВ ---\n";
    // 1. Динамический массив объектов
    std::vector<PlayerCharacter> army;
    army.push_back(PlayerCharacter(12, 12, 12, 10, 10, 10, "Стражник 1", 2, 20, "Воин"));

    // 2. Массив динамических объектов
    std::vector<std::unique_ptr<PlayerCharacter>> tavern;
    tavern.push_back(std::make_unique<PlayerCharacter>(14, 10, 16, 8, 8, 18, "Стражник 2", 3, 25, "Воин"));

    // Работа unique_ptr
    std::cout << "\n--- UNIQUE_PTR ---\n";
    std::cout << "Объект уничтожается при выходе из блока без вызова delete:\n";
    {
        std::unique_ptr<Party> partyTemp = std::make_unique<Party>();
    }
    // Передача владения через std::move
    std::cout << "Передача владения через std::move:\n";
    std::unique_ptr<Party> partyTemp1 = std::make_unique<Party>();
    std::cout << "Объект Party в partyTemp1 (partyTemp1 == nullptr: " << std::boolalpha << (partyTemp1 == nullptr)
              << ")\n";
    std::unique_ptr<Party> partyTemp2;
    std::cout << "partyTemp2 == nullptr: " << std::boolalpha << (partyTemp2 == nullptr) << "\n";
    std::cout << "Передача владения...\n";
    partyTemp2 = std::move(partyTemp1);
    std::cout << "partyTemp1 == nullptr: " << std::boolalpha << (partyTemp1 == nullptr) << "\n";
    std::cout << "partyTemp2 == nullptr: " << std::boolalpha << (partyTemp2 == nullptr) << "\n";

    // Работа shared_ptr
    std::cout << "\n--- SHARED_PTR ---\n";
    {
        std::shared_ptr<Party> partyShared = std::make_shared<Party>();
        std::cout << "Счетчик владельцев: " << partyShared.use_count() << "\n";
        {
            std::shared_ptr<Party> partyShared2 = partyShared;
            std::cout << "Счетчик владельцев: " << partyShared.use_count() << "\n";
        }
        std::cout << "Счетчик владельцев: " << partyShared.use_count() << "\n";
    }

    // Работа weak_ptr
    std::cout << "\n--- WEAK_PTR ---\n";
    std::weak_ptr<PlayerCharacter> party_;
    {
        std::shared_ptr<PlayerCharacter> party =
            std::make_shared<PlayerCharacter>(12, 12, 12, 10, 10, 10, "Богдан Милорад Тихоншвили", 2, 20, "Колдун");
        party_ = party;
        if (std::shared_ptr<PlayerCharacter> partyTemp = party_.lock())
        {
            std::cout << "Объект находится в памяти:\n";
            partyTemp->PrintInfo();
        }
        else
        {
            std::cout << "Объект был удален\n";
        }
    }
    if (std::shared_ptr<PlayerCharacter> partyTemp = party_.lock())
    {
        std::cout << "Объект находится в памяти:\n";
        partyTemp->PrintInfo();
    }
    else
    {
        std::cout << "Объект был удален\n";
    }

    // Демонстрационная программа, полиморфизм, поверхностное и глубокое копирование
    std::cout << "\n--- ДЕМОНСТРАЦИОННАЯ ПРОГРАММА ЛР 4 ---\n";
    std::cout << "Количество существ: " << BaseCreature::GetCreatureCount() << "\n\n";

    {
        std::vector<std::unique_ptr<BaseCreature>> creatures;
        creatures.push_back(
            std::make_unique<PlayerCharacter>(12, 14, 13, 10, 11, 16, "Богдан Милорад Тихоншвили", 3, 24, "Колдун"));
        creatures.push_back(std::make_unique<EnemyCreature>(10, 14, 10, 8, 8, 6, "Гоблин", 7, 0.25, 50, "Гуманоид"));
        creatures.push_back(std::make_unique<EnemyCreature>());

        for (const std::unique_ptr<BaseCreature>& creature : creatures)
        {
            creature->PrintInfo();
            creature->TakeTurn();
            std::cout << "\n";
        }

        // Клонирование через виртуальный метод Clone()
        creatures.push_back(creatures[0]->Clone()); // Глубокая копия (PlayerCharacter)
        creatures.push_back(creatures[1]->Clone()); // Поверхностная копия (EnemyCreature)
        std::cout << "Существ после клонирования: " << BaseCreature::GetCreatureCount() << "\n";

        creatures[3]->SetStrength(20); // Изменение силы у клона игрока
        creatures[4]->SetStrength(20); // Изменение силы у клона врага

        std::cout << "Значение силы после ее изменения у копий:\n";
        std::cout << "Игрок - оригинал: " << creatures[0]->GetStrength() << ", копия: " << creatures[3]->GetStrength()
                  << "\n";
        std::cout << "Враг - оригинал: " << creatures[1]->GetStrength() << ", копия: " << creatures[4]->GetStrength()
                  << "\n\n";
    }

    std::cout << "\nСуществ после очистки вектора: " << BaseCreature::GetCreatureCount() << "\n\n";

    // Работа со строками и указателем this
    {
        auto member = std::make_shared<PlayerCharacter>(12, 10, 12, 10, 10, 10,
                                                        "Иван-Джон-Константин-Пьер-Маркус-Роман I", 4, 30, "Плут");
        Party party(member);
        party.PrintParty();

        std::cout << std::boolalpha;
        std::cout << "Поиск по подстроке \"Пьер\" (find): " << party.SearchCharacter("Пьер") << "\n";
        std::cout << "Поиск по полному имени \"Пьер\" (==): " << party.SearchCharacterByFullName("Пьер") << "\n";

        member->LeaveParty(party);
        party.PrintParty();
    }

    // Демонстрационная программа, полиморфизм, интерфейс и исключения
    std::cout << "\n--- ДЕМОНСТРАЦИОННАЯ ПРОГРАММА ЛР 5 ---\n";
    EnemyCreature goblin(10, 14, 10, 8, 8, 6, "Гоблин", 7, 0.25, 50, "Гуманоид");
    TreasureChest chest("Древний сундук", 120, 20);
    Party party({character1, character2, character3});

    std::cout << "\nРабота интерфейса Ilootable:\n";
    std::vector<const Ilootable*> lootSources = {&goblin, &chest};
    for (const Ilootable* source : lootSources)
    {
        party.DistributeReward(*source);
        std::cout << "\n";
    }

    // Раннее и позднее связывание
    std::cout << "Раннее и позднее связывание:\n";
    std::unique_ptr<BaseCreature> hero =
        std::make_unique<PlayerCharacter>(12, 14, 13, 10, 11, 16, "Богдан Милорад Тихоншвили", 3, 24, "Колдун");

    std::cout << "\nВызов через указатель на BaseCreature невиртуального метода:\n";
    hero->PrintCategory();
    std::cout << "Вызов через указатель на BaseCreature виртуального метода:\n";
    hero->TakeTurn();
    std::cout << "\n";

    // Проверка типа во время выполнения
    std::vector<std::unique_ptr<BaseCreature>> battlefield;
    battlefield.push_back(
        std::make_unique<PlayerCharacter>(12, 14, 13, 10, 11, 16, "Богдан Милорад Тихоншвили", 3, 24, "Колдун"));
    battlefield.push_back(std::make_unique<EnemyCreature>(10, 14, 10, 8, 8, 6, "Гоблин", 7, 0.25, 50, "Гуманоид"));
    battlefield.push_back(std::make_unique<EnemyCreature>(16, 12, 16, 7, 11, 10, "Орк", 15, 0.5, 100, "Гуманоид"));

    std::cout << "\nПроверка типа во время выполнения:\n";
    for (const std::unique_ptr<BaseCreature>& creature : battlefield)
    {
        if (auto* lootable = dynamic_cast<Ilootable*>(creature.get()))
        {
            party.DistributeReward(*lootable);
        }
        else
        {
            std::cout << creature->GetName() << " не реализует ILootable. Добычи нет.\n";
        }
    }

    // Конфигурирование
    std::cout << "\nКонфигурирование:\n";
    PlayerCharacter barbarian(16, 12, 16, 8, 10, 10, "Грог", 5, 60, "Варвар");

    barbarian.TakeDamage(15);
    std::cout << "Текущее HP: " << barbarian.GetCurrentHp() << "\n";

    // Динамическая смена поведения
    barbarian.SetDamagePolicy(std::make_unique<ResistanceDamagePolicy>());
    barbarian.TakeDamage(15);
    std::cout << "Текущее HP: " << barbarian.GetCurrentHp() << "\n";

    // Динамическая смена поведения
    barbarian.SetDamagePolicy(std::make_unique<VulnerabilityDamagePolicy>());
    barbarian.TakeDamage(15);
    std::cout << "Текущее HP: " << barbarian.GetCurrentHp() << "\n";

    // Исключения
    std::cout << "\nИсключения:\n";

    PlayerCharacter testHero(14, 12, 14, 10, 10, 12, "Грог", 19, 45, "Воин");

    // 1. Успешное действие
    try
    {
        testHero.LevelUp();
        testHero.TakeDamage(10);
        testHero.Heal(5);
        std::cout << "Успешно: уровень " << testHero.GetLevel() << ", HP " << testHero.GetCurrentHp() << "\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "Неожиданная ошибка: " << e.what() << "\n";
    }

    // Перехват нарушений правил
    std::cout << "\nПовышение уровня выше 20:\n";
    try
    {
        testHero.LevelUp();
    }
    catch (const GameRuleException& e)
    {
        std::cout << "GameRuleException: " << e.what() << "\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }

    std::cout << "\nУстановка показателя силы = 25:\n";
    try
    {
        testHero.SetStrength(25);
    }
    catch (const InvalidStatException& e)
    {
        std::cout << "InvalidStatException: " << e.what() << "\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }

    std::cout << "\nОтрицательный урон:\n";
    try
    {
        testHero.TakeDamage(-1);
    }
    catch (const InvalidStatException& e)
    {
        std::cout << "InvalidStatException: " << e.what() << "\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }

    std::cout << "\n";

    while (!testHero.IsDead())
    {
        testHero.TakeDamage(1000);
        testHero.TakeDamage(1000);
        testHero.TakeDamage(1000);
        testHero.TakeDamage(1000);
        testHero.TakeTurn();
    }

    std::cout << "\nПопытка исцелить мертвого персонажа:\n";
    try
    {
        testHero.Heal(1);
    }
    catch (const DeadCreatureException& e)
    {
        std::cout << "DeadCreatureException: " << e.what() << "\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }

    std::cout << "\n";

    return 0;
}