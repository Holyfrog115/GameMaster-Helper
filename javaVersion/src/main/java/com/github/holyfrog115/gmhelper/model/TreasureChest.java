package com.github.holyfrog115.gmhelper.model;

import com.github.holyfrog115.gmhelper.exception.InvalidStatException;

public class TreasureChest implements Lootable {
    private final String chestName;
    private final int gold;
    private final int xp;

    public TreasureChest(String chestName, int gold, int xp) {
        if (gold < 0) {
            throw new InvalidStatException("Значение золота должно быть >= 0");
        }
        if (xp < 0) {
            throw new InvalidStatException("Значение опыта должно быть >= 0");
        }

        this.chestName = chestName;
        this.gold = gold;
        this.xp = xp;
    }

    @Override
    public int getXpReward() {
        return xp;
    }

    @Override
    public int getGoldReward() {
        return gold;
    }

    @Override
    public String getLootDescription() {
        return """
                 Награды из %s:
                 - %d золота
                 - %d опыта
                """.formatted(chestName, gold, xp);
    }
}
