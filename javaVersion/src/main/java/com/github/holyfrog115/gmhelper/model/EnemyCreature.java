package com.github.holyfrog115.gmhelper.model;

public class EnemyCreature extends BaseCreature {
    private double challengeRating;
    private int xpReward;
    private String type;

    public EnemyCreature(int str, int dex, int con, int intelligence, int wis, int cha, String name,
                         int maxHp, double challengeRating, int xpReward, String type) {
        super(name, maxHp, str, dex, con, intelligence, wis, cha);
        this.type = type;

        if (challengeRating < 0) {
            System.out.println("Ошибка. Уровень опасности существа не может быть < 0. Установлено значение 0.");
            this.challengeRating = 0;
        } else {
            this.challengeRating = challengeRating;
        }

        if (xpReward < 0) {
            System.out.println("Ошибка. Количество опыта за победу над существом не может быть < 0. Установлено значение 0.");
            this.xpReward = 0;
        } else {
            this.xpReward = xpReward;
        }

        System.out.println("EnemyCreature() -> Объект создан");
    }

    public EnemyCreature() {
        this(10, 10, 10, 10, 10, 10, "", 1, 0, 0, "");
    }

    public EnemyCreature(EnemyCreature other) {
        super(other); // Поверхностное копирование ссылки attributes в BaseCreature
        this.challengeRating = other.challengeRating;
        this.xpReward = other.xpReward;
        this.type = other.type;
    }

    @Override
    public EnemyCreature clone() {
        return new EnemyCreature(this);
    }

    public double getChallengeRating() {
        return challengeRating;
    }

    public int getXpReward() {
        return xpReward;
    }

    public String getType() {
        return type;
    }

    public void setChallengeRating(double challengeRating) {
        if (challengeRating < 0) {
            System.out.println("Ошибка. Уровень опасности существа не может быть < 0");
            return;
        }
        this.challengeRating = challengeRating;
    }

    public void setXpReward(int xpReward) {
        if (xpReward < 0) {
            System.out.println("Ошибка. Количество опыта за победу над существом не может быть < 0");
            return;
        }
        this.xpReward = xpReward;
    }

    public void setType(String type) {
        this.type = type;
    }

    @Override
    public String toString() {
        String displayName = getName();
        if (displayName.length() > 64) {
            displayName = displayName.substring(0, 64) + "...";
        }
        return """
             - Существо: %s
             - Максимальное здоровье: %d
             - Текущее здоровье: %d
             - Тип существа: %s
             - Уровень опасности: %s
             - Награда за победу: %d опыта
             - Характеристики:
            %s""".formatted(
                displayName,
                getMaxHp(),
                getCurrentHp(),
                type,
                challengeRating,
                xpReward,
                attributes
        );
    }

    @Override
    public void takeTurn() {
        if (getCurrentHp() == 0) {
            System.out.println(getName() + " погиб.");
            // Награда за победу над врагом добавляется в результаты битвы в трекере ходов
            // После чего существо удаляется из трекера
        } else {
            // Совершает ход
            System.out.println(getName() + " совершает атаку.");
        }
    }
}