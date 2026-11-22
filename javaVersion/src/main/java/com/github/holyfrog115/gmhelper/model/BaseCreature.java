package com.github.holyfrog115.gmhelper.model;
import com.github.holyfrog115.gmhelper.exception.InvalidStatException;
import com.github.holyfrog115.gmhelper.utils.DiceUtils;

public abstract class BaseCreature {
    private String name;
    private int currentHp;
    private int maxHp;
    private DamagePolicy damagePolicy = new NormalDamagePolicy();
    private static int creatureCount = 0;

    protected Attributes attributes;

    public BaseCreature(String name, int maxHp, int strength, int dexterity, int constitution,
                        int intelligence, int wisdom, int charisma) {
        this.name = name;
        this.attributes = new Attributes(strength, dexterity, constitution, intelligence, wisdom, charisma);

        if (maxHp < 1) {
            System.out.println("Ошибка. Неположительное значение максимального здоровья. Установлено значение - 1");
            this.maxHp = 1;
        } else {
            this.maxHp = maxHp;
        }
        this.currentHp = this.maxHp;
        creatureCount++;

        System.out.println("BaseCreature() -> Объект создан");
    }

    public BaseCreature() {
        this("", 1, 10, 10, 10, 10, 10, 10);
    }

    protected BaseCreature(BaseCreature other) {
        this.name = other.getName();
        this.currentHp = other.getCurrentHp();
        this.maxHp = other.getMaxHp();
        this.attributes = other.attributes;
        this.damagePolicy = other.damagePolicy;
        creatureCount++;

        System.out.println("BaseCreature(const BaseCreature& other) -> объект скопирован");
    }

    @Override
    public abstract BaseCreature clone();

    public abstract void takeTurn();

    public static int getCreatureCount() {
        return creatureCount;
    }

    public String getName() {
        return name;
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

    public void setName(String name) {
        this.name = name;
    }

    public void setCurrentHp(int hp) {
        if (hp < 0) {
            this.currentHp = 0;
        } else if (hp > this.maxHp) {
            this.currentHp = this.maxHp;
        } else {
            this.currentHp = hp;
        }
    }

    public void setMaxHp(int hp) {
        if (hp < 1) {
            this.maxHp = 1;
        } else {
            this.maxHp = hp;
        }
        if (this.currentHp > this.maxHp) {
            this.currentHp = this.maxHp;
        }
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
            throw new InvalidStatException("Значение урона не может быть отрицательным.");
        }

        int actualDamage = damagePolicy.modifyDamage(damage);
        System.out.println(name + " получает " + actualDamage + " урона (базовый: " + damage
                + ", правило: " + damagePolicy.getPolicyName() + ")");
        if (currentHp - actualDamage < 0) {
            currentHp = 0;
        } else {
            currentHp -= actualDamage;
        }
    }

    public void heal(int heal) {
        if (heal < 0) {
            System.out.println("Ошибка. Значение исцеления должно быть положительным.");
            return;
        }
        if (currentHp + heal > maxHp) {
            currentHp = maxHp;
        } else {
            currentHp += heal;
        }
    }

    public int rollInitiative() {
        return DiceUtils.rollD20() + calculateModifier("dex");
    }

    public int calculateModifier(String attribute) {
        return attributes.calculateModifier(attribute);
    }

    @Override
    public String toString() {
        String displayName = getName();
        if (displayName.length() > 64) {
            displayName = displayName.substring(0, 64) + "...";
        }
        return """
             - Имя персонажа: %s
             - Максимальное здоровье: %d
             - Текущее здоровье: %d""".formatted(displayName, getMaxHp(), getCurrentHp());
    }

    public static void printCategory() {
        System.out.println("Категория: Базовое существо");
    }

    public void setDamagePolicy(DamagePolicy policy) {
        if (policy != null) {
            this.damagePolicy = policy;
        }
    }
}
