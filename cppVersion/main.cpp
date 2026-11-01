#include "attributes.hpp"
#include "party.hpp"
#include "playercharacter.hpp"
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
    std::shared_ptr<PlayerCharacter> character1 =
        std::make_shared<PlayerCharacter>(10, 10, 10, 14, 12, 15, "Робослав", 5, 65);
    std::shared_ptr<PlayerCharacter> character2 =
        std::make_shared<PlayerCharacter>(16, 10, 14, 8, 8, 10, "Иван-Джон-Пьер", 6, 105);
    std::shared_ptr<PlayerCharacter>& character2ref = character2;
    std::shared_ptr<PlayerCharacter> character3 =
        std::make_shared<PlayerCharacter>(8, 8, 8, 15, 15, 12, "Нилбог", 4, 32);

    // Вызов методов класса PlayerCharacter, которые используют методы класса Attributes
    std::cout << "Вызов методов класса PlayerCharacter:\n";
    character1->TakeDamage(1000);
    character1->Heal(10);
    character1->PrintInfo();
    std::cout << "Модификатор силы объекта character2: " << character2ref->CalculateModifier("str") << "\n";
    std::cout << "Бросок инициативы объекта character3: " << character3->RollInitiative() << "\n";

    std::cout << "При инициализации объекта класса PlayerCharacter создается объект класса Attributes:\n";
    {
        PlayerCharacter character4(8, 8, 8, 15, 15, 12, "Пример композиции", 4, 32);
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

    // Примеры работы проверок правил
    std::cout << "\n--- ПРИМЕРЫ РАБОТЫ ПРОВЕРОК ПРАВИЛ ---\n";
    std::cout << "Установление отрицательного значения характеристики:\n";
    character1->SetCharisma(-1);
    std::cout << "Установление значения характеристики > 20:\n";
    character1->SetCharisma(30);
    std::cout << "Попытка повысить уровень выше 20:\n";
    character1->SetLevel(18);
    for (int i = 0; i < 3; ++i)
    {
        character1->LevelUp();
    }

    // Статическая инициализация объекта
    std::cout << "\n--- СТАТИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТА ---\n";
    {
        static PlayerCharacter staticCharacter(10, 10, 10, 10, 10, 10, "Статик", 10, 10);
    }

    // Динамическая инициализация объекта
    std::cout << "\n--- ДИНАМИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТА ---\n";
    std::unique_ptr<PlayerCharacter> dynamicCharacter;
    {
        dynamicCharacter = std::make_unique<PlayerCharacter>(10, 10, 10, 10, 10, 10, "Динамическая память", 10, 10);
    }
    std::cout << "Имя: " << dynamicCharacter->GetName() << "\n";

    // Тест массивов
    std::cout << "\n--- ТЕСТ МАССИВОВ ---\n";
    // 1. Динамический массив объектов
    std::vector<PlayerCharacter> army;
    army.push_back(PlayerCharacter(12, 12, 12, 10, 10, 10, "Стражник 1", 2, 20));

    // 2. Массив динамических объектов
    std::vector<std::unique_ptr<PlayerCharacter>> tavern;
    tavern.push_back(std::make_unique<PlayerCharacter>(14, 10, 16, 8, 8, 18, "Стражник 2", 3, 25));

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
            std::make_shared<PlayerCharacter>(12, 12, 12, 10, 10, 10, "Богдан Милорад Тихоншвили", 2, 20);
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

    std::cout << "\n";

    return 0;
}