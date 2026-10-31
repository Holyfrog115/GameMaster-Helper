package com.github.holyfrog115.gmhelper.model;

public class Attributes {
    private int strength;
    private int dexterity;
    private int constitution;
    private int intelligence;
    private int wisdom;
    private int charisma;

    public Attributes(int strength, int dexterity, int constitution, int intelligence, int wisdom, int charisma) {
        this.strength = validAttribute(strength);
        this.dexterity = validAttribute(dexterity);
        this.constitution = validAttribute(constitution);
        this.intelligence = validAttribute(intelligence);
        this.wisdom = validAttribute(wisdom);
        this.charisma = validAttribute(charisma);
    }

    // get методы

    public int getStrength() {
        return strength;
    }

    public int getDexterity() {
        return dexterity;
    }

    public int getCharisma() {
        return charisma;
    }

    public int getConstitution() {
        return constitution;
    }

    public int getIntelligence() {
        return intelligence;
    }

    public int getWisdom() {
        return wisdom;
    }

    // set методы

    public void setCharisma(int charisma) {
        this.charisma = validAttribute(charisma);
    }

    public void setConstitution(int constitution) {
        this.constitution = validAttribute(constitution);
    }

    public void setDexterity(int dexterity) {
        this.dexterity = validAttribute(dexterity);
    }

    public void setIntelligence(int intelligence) {
        this.intelligence = validAttribute(intelligence);
    }

    public void setStrength(int strength) {
        this.strength = validAttribute(strength);
    }

    public void setWisdom(int wisdom) {
        this.wisdom = validAttribute(wisdom);
    }

    public int calculateModifier(String attribute) {
        attribute = attribute.toLowerCase();
        return switch (attribute) {
            case "str", "strength" -> (strength - 10) / 2;
            case "dex", "dexterity" -> (dexterity - 10) / 2;
            case "con", "constitution" -> (constitution - 10) / 2;
            case "int", "intelligence" -> (intelligence - 10) / 2;
            case "wis", "wisdom" -> (wisdom - 10) / 2;
            case "cha", "charisma" -> (charisma - 10) / 2;
            default -> 0;
        };
    }

    public int calculateCarryingCapacity() {
        return strength * 15;
    }

    private int validAttribute(int attribute) {
        if (attribute < 1) {
            System.out.println("Ошибка. Неположительное значение характеристики. Установлено значение 1.");
            return 1;
        }
        else if (attribute > 20) {
            System.out.println("Ошибка. Значение характеристики > 20. Установлено значение 20.");
            return 20;
        }
        return attribute;
    }

    @Override
    public String toString() {
        return """
           +-----+-----+-----+-----+-----+-----+
           | СИЛ | ЛОВ | ТЕЛ | ИНТ | МУД | ХАР |
           +-----+-----+-----+-----+-----+-----+
           | %3d | %3d | %3d | %3d | %3d | %3d |
           +-----+-----+-----+-----+-----+-----+
           """.formatted(strength, dexterity, constitution, intelligence, wisdom, charisma);
    }
}
