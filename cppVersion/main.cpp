#include "attributes.hpp"
#include "party.hpp"
#include "playercharacter.hpp"
#include <iostream>
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
    PlayerCharacter character1(10, 10, 10, 14, 12, 15, "Робослав", 5, 65);
    PlayerCharacter character2(16, 10, 14, 8, 8, 10, "Иван-Джон-Пьер", 6, 105);
    PlayerCharacter& character2ref = character2;
    PlayerCharacter character3(8, 8, 8, 15, 15, 12, "Нилбог", 4, 32);

    // Вызов методов класса PlayerCharacter, которые используют методы класса Attributes
    std::cout << "Вызов методов класса PlayerCharacter:\n";
    character1.TakeDamage(1000);
    character1.Heal(10);
    character1.PrintInfo();
    std::cout << "Модификатор силы объекта character2: " << character2ref.CalculateModifier("str") << "\n";
    std::cout << "Бросок инициативы объекта character3: " << character3.RollInitiative() << "\n";

    std::cout << "При инициализации объекта класса PlayerCharacter создается объект класса Attributes:\n";
    {
        PlayerCharacter character4(8, 8, 8, 15, 15, 12, "Пример композиции", 4, 32);
        std::cout << "При удалении объекта класса Playercharacter удаляется и объект класса Attributes:\n";
    }

    // Агрегация
    std::cout << "\n--- АГРЕГАЦИЯ: ---\n";
    {
        Party party({&character1, &character2ref, &character3});

        // Вызов методов класса Party, которые используют методы методы класса PlayerCharacter
        std::cout << "Вызов методов класса Party:\n";
        party.PrintParty();
        party.RemoveCharacter(3);
        std::cout << "После удаления персонажа:\n";
        party.PrintParty();
        std::cout << "Средний уровень группы: " << party.CalcAvgLevel() << "\n";
    }
    std::cout << "После удаления объекта Party персонажи все еще доступны. Имя объекта charachter1: "
              << character1.GetName() << "\n";

    // Примеры работы проверок правил
    std::cout << "\n--- ПРИМЕРЫ РАБОТЫ ПРОВЕРОК ПРАВИЛ ---\n";
    std::cout << "Установление отрицательного значения характеристики:\n";
    character1.SetCharisma(-1);
    std::cout << "Установление значения характеристики > 20:\n";
    character1.SetCharisma(30);
    std::cout << "Попытка повысить уровень выше 20:\n";
    character1.SetLevel(18);
    for (int i = 0; i < 3; ++i)
    {
        character1.LevelUp();
    }

    // Статическая инициализация объекта
    std::cout << "\n--- СТАТИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТА ---\n";
    {
        static PlayerCharacter staticCharacter(10, 10, 10, 10, 10, 10, "Статик", 10, 10);
    }

    // Динамическая инициализация объекта
    std::cout << "\n--- ДИНАМИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТА ---\n";
    PlayerCharacter* dynamicCharacter;
    {
        dynamicCharacter = new PlayerCharacter(10, 10, 10, 10, 10, 10, "Динамическая память", 10, 10);
    }
    std::cout << "Имя: " << dynamicCharacter->GetName() << "\n";
    delete dynamicCharacter;

    // Тест массивов
    std::cout << "\n--- ТЕСТ МАССИВОВ ---\n";
    // 1. Динамический массив объектов
    std::vector<PlayerCharacter> army;
    army.push_back(PlayerCharacter(12, 12, 12, 10, 10, 10, "Стражник 1", 2, 20));

    // 2. Массив динамических объектов
    std::vector<PlayerCharacter*> tavern;
    tavern.push_back(new PlayerCharacter(14, 10, 16, 8, 8, 18, "Стражник 2", 3, 25));
    delete tavern[0];

    std::cout << "\n";

    return 0;
}