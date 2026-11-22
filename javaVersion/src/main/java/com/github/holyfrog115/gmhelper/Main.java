package com.github.holyfrog115.gmhelper;

import com.github.holyfrog115.gmhelper.exception.DeadCreatureException;
import com.github.holyfrog115.gmhelper.exception.GameRuleException;
import com.github.holyfrog115.gmhelper.exception.InvalidStatException;
import com.github.holyfrog115.gmhelper.model.*;

import java.lang.ref.WeakReference;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        // Композиция
        System.out.println("--- КОМПОЗИЦИЯ ---");
        PlayerCharacter character1 = new PlayerCharacter(10, 10, 10, 14, 12,
                15, "Робослав", 5, 65, "Воин");
        PlayerCharacter character2 = new PlayerCharacter(16, 10, 14, 8, 8,
                10, "Иван-Джон-Пьер", 6, 105, "Варвар");
        PlayerCharacter character3 = new PlayerCharacter(8, 8, 8, 15, 15,
                12, "Нилбог", 4, 32, "Жрец");
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
                "temp", 1, 10, "")) {}

        // РАБОТА СБОРЩИКА МУСОРА
        System.out.println("\n--- РАБОТА СБОРЩИКА МУСОРА ---");
        WeakReference<PlayerCharacter> watcher;
        {
            System.out.println("Создание объекта во внутреннем блоке");
            PlayerCharacter characterTemp = new PlayerCharacter(10, 10, 10, 10, 10, 10,
                    "temp", 1, 10, "");
            watcher = new WeakReference<>(characterTemp);
            characterTemp = null;
            System.out.println("Выход из блока");
        }
        System.out.println((watcher.get() != null) + ": объект жив"); // true
        System.out.println("На объект не указывают ссылки. Принудительный запуск сборщика мусора");
        System.gc();
        System.out.println((watcher.get() != null) + ": объект уничтожен"); // false

        // ДЕМОНСТРАЦИОННАЯ ПРОГРАММА: ПОЛИМОРФИЗМ, ПОВЕРХНОСТНОЕ И ГЛУБОКОЕ КОПИРОВАНИЕ
        System.out.println("\n--- ДЕМОНСТРАЦИОННАЯ ПРОГРАММА ЛР 4 ---");
        System.out.println("Количество существ: " + BaseCreature.getCreatureCount() + "\n");

        {
            List<BaseCreature> creatures = new ArrayList<>();
            creatures.add(new PlayerCharacter(12, 14, 13, 10, 11, 16,
                    "Богдан Милорад Тихоншвили", 3, 24, "Колдун"));
            creatures.add(new EnemyCreature(10, 14, 10, 8, 8, 6,
                    "Гоблин", 7, 0.25, 50, "Гуманоид"));
            creatures.add(new EnemyCreature());

            for (BaseCreature creature : creatures) {
                System.out.println(creature);
                creature.takeTurn();
                System.out.println();
            }

            // Клонирование через переопределённый метод clone()
            creatures.add(creatures.get(0).clone()); // Глубокая копия (PlayerCharacter)
            creatures.add(creatures.get(1).clone()); // Поверхностная копия (EnemyCreature)
            System.out.println("Существ после клонирования: " + BaseCreature.getCreatureCount());

            creatures.get(3).setStrength(20); // Изменение силы у клона игрока
            creatures.get(4).setStrength(20); // Изменение силы у клона врага

            System.out.println("Значение силы после ее изменения у копий:");
            System.out.println("Игрок - оригинал: " + creatures.get(0).getStrength()
                    + ", копия: " + creatures.get(3).getStrength());
            System.out.println("Враг - оригинал: " + creatures.get(1).getStrength()
                    + ", копия: " + creatures.get(4).getStrength() + "\n");
        }

        // РАБОТА СО СТРОКАМИ И ССЫЛКОЙ THIS
        System.out.println("--- РАБОТА СО СТРОКАМИ И ССЫЛКОЙ THIS ---");
        {
            PlayerCharacter member = new PlayerCharacter(12, 10, 12, 10, 10, 10,
                    "Иван-Джон-Константин-Пьер-Маркус-Роман I", 4, 30, "Плут");
            Party party = new Party(member);
            System.out.println(party);

            System.out.println("Поиск по подстроке \"Пьер\" (contains): " + party.searchCharacter("Пьер"));
            System.out.println("Поиск по полному имени \"Пьер\" (equals): " + party.searchCharacterByFullName("Пьер"));

            member.leaveParty(party);
            System.out.println(party);
        }

        System.out.println("\n--- ДЕМОНСТРАЦИОННАЯ ПРОГРАММА ЛР 5 ---");
        EnemyCreature goblin = new EnemyCreature(10, 14, 10, 8, 8, 6, "Гоблин", 7, 0.25, 50, "Гуманоид");
        TreasureChest chest = new TreasureChest("Древний сундук", 120, 20);
        Party lab5Party = new Party(List.of(character1, character2, character3));

        System.out.println("\nРабота интерфейса Lootable:");
        List<Lootable> lootSources = List.of(goblin, chest);
        for (Lootable source : lootSources) {
            lab5Party.distributeReward(source);
            System.out.println();
        }

        // Раннее и позднее связывание
        System.out.println("Раннее и позднее связывание:");
        BaseCreature hero = new PlayerCharacter(
                12, 14, 13, 10, 11, 16, "Богдан Милорад Тихоншвили", 3, 24, "Колдун");

        System.out.println("\nВызов через ссылку BaseCreature static-метода (раннее связывание):");
        hero.printCategory();
        System.out.println("Вызов через ссылку BaseCreature переопределенного метода (позднее связывание):");
        hero.takeTurn();
        System.out.println();

        // Проверка типа во время выполнения
        List<BaseCreature> battlefield = new ArrayList<>();
        battlefield.add(new PlayerCharacter(
                12, 14, 13, 10, 11, 16, "Богдан Милорад Тихоншвили", 3, 24, "Колдун"));
        battlefield.add(new EnemyCreature(10, 14, 10, 8, 8, 6, "Гоблин", 7, 0.25, 50, "Гуманоид"));
        battlefield.add(new EnemyCreature(16, 12, 16, 7, 11, 10, "Орк", 15, 0.5, 100, "Гуманоид"));

        System.out.println("\nПроверка типа во время выполнения (instanceof):");
        for (BaseCreature creature : battlefield) {
            if (creature instanceof Lootable lootable) {
                lab5Party.distributeReward(lootable);
            } else {
                System.out.println(creature.getName() + " не реализует Lootable. Добычи нет.");
            }
        }

        // Стандартный интерфейс Comparable - сортировка существ по имени
        System.out.println("\nСортировка существ по имени (Comparable):");
        Collections.sort(battlefield);
        for (BaseCreature creature : battlefield) {
            System.out.println(" - " + creature.getName());
        }

        // Конфигурирование (Strategy)
        System.out.println("\nКонфигурирование:");
        PlayerCharacter barbarian = new PlayerCharacter(16, 12, 16, 8, 10, 10, "Грог", 5, 60, "Варвар");

        barbarian.takeDamage(15);
        System.out.println("Текущее HP: " + barbarian.getCurrentHp());

        // Динамическая смена поведения
        barbarian.setDamagePolicy(new ResistanceDamagePolicy());
        barbarian.takeDamage(15);
        System.out.println("Текущее HP: " + barbarian.getCurrentHp());

        // Динамическая смена поведения
        barbarian.setDamagePolicy(new VulnerabilityDamagePolicy());
        barbarian.takeDamage(15);
        System.out.println("Текущее HP: " + barbarian.getCurrentHp());

        // Исключения
        System.out.println("\nИсключения:");
        try (PlayerCharacter testHero = new PlayerCharacter(14, 12, 14, 10, 10, 12, "Грог", 19, 45, "Воин")) {

            // 1. Успешное действие
            try {
                testHero.levelUp();
                testHero.takeDamage(10);
                testHero.heal(5);
                System.out.println("Успешно: уровень " + testHero.getLevel() + ", HP " + testHero.getCurrentHp());
            } catch (Exception e) {
                System.out.println("Неожиданная ошибка: " + e.getMessage());
            }

            // Перехват нарушений правил
            System.out.println("\nПовышение уровня выше 20:");
            try {
                testHero.levelUp();
            } catch (GameRuleException e) {
                System.out.println("GameRuleException: " + e.getMessage());
            }

            System.out.println("\nУстановка показателя силы = 25:");
            try {
                testHero.setStrength(25);
            } catch (InvalidStatException e) {
                System.out.println("InvalidStatException: " + e.getMessage());
            }

            System.out.println("\nОтрицательный урон:");
            try {
                testHero.takeDamage(-1);
            } catch (InvalidStatException e) {
                System.out.println("InvalidStatException: " + e.getMessage());
            }

            System.out.println();

            while (!testHero.isDead()) {
                testHero.takeDamage(1000);
                testHero.takeDamage(1000);
                testHero.takeDamage(1000);
                testHero.takeDamage(1000);
                testHero.takeTurn();
            }

            System.out.println("\nПопытка исцелить мертвого персонажа:");
            try {
                testHero.heal(1);
            } catch (DeadCreatureException e) {
                System.out.println("DeadCreatureException: " + e.getMessage());
            } finally {
                System.out.println("Блок finally выполнен независимо от исхода.");
            }
        }
    }
}
