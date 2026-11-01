package com.github.holyfrog115.gmhelper;

import com.github.holyfrog115.gmhelper.model.Party;
import com.github.holyfrog115.gmhelper.model.PlayerCharacter;

import java.lang.ref.WeakReference;
import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        // Композиция
        System.out.println("--- КОМПОЗИЦИЯ ---");
        PlayerCharacter character1 = new PlayerCharacter(10, 10, 10, 14, 12,
                15, "Робослав", 5, 65);
        PlayerCharacter character2 = new PlayerCharacter(16, 10, 14, 8, 8,
                10, "Иван-Джон-Пьер", 6, 105);
        PlayerCharacter character3 = new PlayerCharacter(8, 8, 8, 15, 15,
                12, "Нилбог", 4, 32);
        System.out.println("Состояние после вызова методов класса PlayerCharacter, использующих объект класса Attributes:");
        character1.takeDamage(1000);
        character1.heal(10);
        System.out.println(character1);
        System.out.println("Модификатор силы объекта character2: " + character2.calculateModifier("str"));
        System.out.println("Бросок инициативы объекта character3: " + character3.rollInitiative());

        // Агрегация
        System.out.println("\n--- АГРЕГАЦИЯ ---");
        {
            Party party = new Party(Arrays.asList(character1, character2, character3));

            System.out.println("Состав группы после создания:");
            System.out.println(party);

            party.removeCharacter(3);
            System.out.println("Состав группы после удаления 3-го персонажа:");
            System.out.println(party);
            System.out.println("Средний уровень группы: " + party.calcAvgLevel());
        }
        System.out.println("Группа удалена, но персонажи существуют независимо. Имя первого: " + character1.getName());

        // ПРОВЕРКА ПРАВИЛ ПРЕДМЕТНОЙ ОБЛАСТИ
        System.out.println("\n--- ПРОВЕРКА ПРАВИЛ ПРЕДМЕТНОЙ ОБЛАСТИ ---");
        System.out.println("Попытка установить отрицательную харизму (-1):");
        character1.setCharisma(-1);
        System.out.println("Попытка установить харизму выше максимума (30):");
        character1.setCharisma(30);
        System.out.println("Попытка повысить уровень выше 20:");
        character1.setLevel(18);
        for (int i = 0; i < 3; ++i) {
            character1.levelUp();
        }

        // Ссылки и копии
        System.out.println("\n--- ССЫЛКИ И КОПИИ ---");
        PlayerCharacter character2Ref = character2;
        System.out.println("Состояние до изменения через вторую переменную:");
        System.out.println("character2:\n" + character2);
        character2Ref.takeDamage(50);
        character2Ref.setLevel(7);
        System.out.println("Состояние после изменения через secondRef:");
        System.out.println("character2:\n" + character2);
        System.out.println("character2Ref:\n" + character2Ref);
        System.out.println("Обе переменные указывают на один объект в куче: " + (character2 == character2Ref));

        // Освобождение ресурса без деструктора
        System.out.println("\n--- Освобождение ресурса без деструктора ---");
        try (PlayerCharacter characterTemp = new PlayerCharacter(10, 10, 10, 10, 10, 10,
                "temp", 1, 10)) {}

        // РАБОТА СБОРЩИКА МУСОРА
        System.out.println("\n--- РАБОТА СБОРЩИКА МУСОРА ---");
        WeakReference<PlayerCharacter> watcher;
        {
            System.out.println("Создание объекта во внутреннем блоке");
            PlayerCharacter characterTemp = new PlayerCharacter(10, 10, 10, 10, 10, 10,
                    "temp", 1, 10);
            watcher = new WeakReference<>(characterTemp);
            characterTemp = null;
            System.out.println("Выход из блока");
        }
        System.out.println((watcher.get() != null) + ": объект жив"); // true
        System.out.println("На объект не указывают ссылки. Принудительный запуск сборщика мусора");
        System.gc();
        System.out.println((watcher.get() != null) + ": объект уничтожен"); // false
    }
}
