package com.github.holyfrog115.gmhelper.model;
import com.github.holyfrog115.gmhelper.utils.DiceUtils;
import java.util.Objects;

public final class PlayerCharacter extends BaseCreature implements AutoCloseable {
    private int level;
    private int successfulSavingThrows = 0;
    private int failedSavingThrows = 0;
    private boolean isDead = false;
    private String characterClass;

    public PlayerCharacter(int str, int dex, int con, int intel, int wis, int cha,
                           String name, int level, int maxHp, String characterClass) {
        super(name, maxHp, str, dex, con, intel, wis, cha);
        this.characterClass = characterClass;

        if (level < 1) {
            System.out.println("Ошибка. Неположительный уровень персонажа. Установлен 1 уровень.");
            this.level = 1;
        } else if (level > 20) {
            System.out.println("Ошибка. Уровень персонажа > 20. Установлен 20 уровень.");
            this.level = 20;
        } else {
            this.level = level;
        }

        System.out.println("PlayerCharacter() -> Объект создан (" + getName() + ")");
    }

    public PlayerCharacter() {
        this(10, 10, 10, 10, 10, 10, "", 1, 1, "");
    }

    public PlayerCharacter(PlayerCharacter other) {
        super(other);
        this.attributes = new Attributes(other.attributes);
        this.characterClass = other.characterClass;
        this.successfulSavingThrows = other.successfulSavingThrows;
        this.failedSavingThrows = other.failedSavingThrows;
        this.isDead = other.isDead;
        this.level = other.level;
        System.out.println("PlayerCharacter(const PlayerCharacter& other) -> объект скопирован");
    }

    @Override
    public PlayerCharacter clone() {
        return new PlayerCharacter(this);
    }

    @Override
    public void close() {
        System.out.println("~PlayerCharacter() -> Объект уничтожен (" + getName() + ")");
    }

    // Get методы

    public int getLevel() {
        return level;
    }

    public boolean isDead() {
        return isDead;
    }

    public String getCharacterClass() {
        return characterClass;
    }

    // Set методы

    public void setLevel(int level) {
        if (level < 1) {
            System.out.println("Ошибка. Неположительный уровень персонажа.");
        } else if (level > 20) {
            System.out.println("Ошибка. Уровень персонажа > 20.");
        } else {
            this.level = level;
        }
    }

    public void setCharacterClass(String characterClass) {
        this.characterClass = characterClass;
    }

    // Основные методы

    public void levelUp() {
        if (level < 20) {
            level++;
            System.out.println("Уровень повышен. Текущий уровень: " + level);
        } else {
            System.out.println("Невозможно повысить уровень. Достигнут максимальный уровень (20).");
        }
    }

    public int calculateCarryingCapacity() {
        return attributes.calculateCarryingCapacity();
    }

    public void leaveParty(Party party) {
        party.removeCharacter(this);
    }

    @Override
    public void takeTurn() {
        if (isDead) {
            return;
        }
        if (getCurrentHp() == 0) {
            if (DiceUtils.rollD20() >= 10) {
                successfulSavingThrows++;
                System.out.println("Успешный спасбросок. (" + successfulSavingThrows + " из 3)");
            } else {
                failedSavingThrows++;
                System.out.println("Провальный спасбросок. (" + failedSavingThrows + " из 3)");
            }

            if (successfulSavingThrows == 3) {
                System.out.println(getName() + " стабилизировался и восстанавливает 1 HP");
                setCurrentHp(1);
            } else if (failedSavingThrows == 3) {
                isDead = true;
                System.out.println(getName() + " погиб.");
            }
        } else {
            successfulSavingThrows = 0;
            failedSavingThrows = 0;
            System.out.println("Персонаж игрока " + getName() + " совершает атаку.");
        }
    }

    @Override
    public String toString() {
        return """
                %s
                 - Класс: %s
                 - Уровень: %d
                 - Характеристики:
                %s""".formatted(super.toString(), characterClass, level, attributes);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        PlayerCharacter character = (PlayerCharacter) obj;
        return level == character.level
                && getMaxHp() == character.getMaxHp()
                && Objects.equals(getName(), character.getName())
                && Objects.equals(characterClass, character.characterClass);
    }

    @Override
    public int hashCode() {
        return Objects.hash(getName(), level, getMaxHp(), characterClass);
    }

    public static void printCategory() {
        System.out.println("Категория: Персонаж игрока");
    }
}