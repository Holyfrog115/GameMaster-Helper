package com.github.holyfrog115.gmhelper.model;
import com.github.holyfrog115.gmhelper.utils.DiceUtils;

import java.awt.*;
import java.util.Objects;

public class PlayerCharacter {
    private String name;
    private int level;
    private int currentHp;
    private int maxHp;
    private Attributes attributes;

    public PlayerCharacter(int str, int dex, int con, int intel, int wis, int cha, String name, int level, int maxHp) {
        this.attributes = new Attributes(str, dex, con, intel, wis, cha);
        this.name = name;
        if (level < 1) {
            System.out.println("Ошибка. Неположительный уровень персонажа. Установлен 1 уровень.");
            this.level = 1;
        }
        else if (level > 20) {
            System.out.println("Ошибка. Уровень персонажа > 20. Установлен 20 уровень.");
            this.level = 20;
        }
        else {
            this.level = level;
        }
        if (maxHp < 1) {
            System.out.println("Ошибка. Неположительное значение максимального здоровья. Установлено значение - 1");
            this.maxHp = 1;
        }
        else {
            this.maxHp = maxHp;
        }
        this.currentHp = maxHp;
    }

    // get методы

    public String getName() {
        return name;
    }

    public int getLevel() {
        return level;
    }

    public int getCurrentHp() {
        return currentHp;
    }

    public int getMaxHp() {
        return maxHp;
    }

    public int getStrength() {
        return attributes.getStrength();
    }

    public int getDexterity() {
        return attributes.getDexterity();
    }

    public int getConstitution() {
        return attributes.getConstitution();
    }

    public int getIntelligence() {
        return attributes.getIntelligence();
    }

    public int getWisdom() {
        return attributes.getWisdom();
    }

    public int getCharisma() {
        return attributes.getCharisma();
    }

    // set методы

    public void setName(String name) {
        this.name = name;
    }

    public void setCurrentHp(int currentHp) {
        this.currentHp = currentHp;
    }

    public void setLevel(int level) {
        this.level = level;
    }

    public void setMaxHp(int maxHp) {
        this.maxHp = maxHp;
    }

    public void setStrength(int strength) {
        attributes.setStrength(strength);
    }

    public void setDexterity(int dexterity) {
        attributes.setDexterity(dexterity);
    }

    public void setConstitution(int constitution) {
        attributes.setConstitution(constitution);
    }

    public void setIntelligence(int intelligence) {
        attributes.setIntelligence(intelligence);
    }

    public void setWisdom(int wisdom) {
        attributes.setWisdom(wisdom);
    }

    public void setCharisma(int charisma) {
        attributes.setCharisma(charisma);
    }


    public void takeDamage(int damage) {
        if (damage < 0) {
            System.out.println("Ошибка. Значение урона должно быть положительным.");
            return;
        }
        if (currentHp - damage < 0) {
            currentHp = 0;
        }
        else {
            currentHp -= damage;
        }
    }

    public void heal(int heal) {
        if (heal < 0) {
            System.out.println("Ошибка. Значение исцеления должно быть положительным.");
            return;
        }
        if (currentHp + heal > maxHp) {
            currentHp = maxHp;
        }
        else {
            currentHp += heal;
        }
    }

    public void levelUp() {
        if (level < 20) {
            level++;
            System.out.println("Уровень повышен. Текущий уровень: " + level);
        }
        else {
            System.out.println("Невозможно повысить уровень. Достигнут максимальный уровень (20).");
        }
    }

    public int calculateModifier(String attribute) {
        return attributes.calculateModifier(attribute);
    }

    public int rollInitiative() {
        return DiceUtils.rollD20() + attributes.calculateModifier("dex");
    }

    public int calculateCarryingCapacity() {
        return attributes.calculateCarryingCapacity();
    }

    @Override
    public String toString() {
        return """
           - Имя персонажа: %s
           - Уровень: %d
           - Максимальное здоровье: %d
           - Текущее здоровье: %d
           - Характеристики:
           %s""".formatted(name, level, maxHp, currentHp, attributes);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        PlayerCharacter character = (PlayerCharacter) obj;
        return Objects.equals(name, character.getName()) && Objects.equals(level, character.getLevel())
                && Objects.equals(maxHp, character.getMaxHp());
    }
}
