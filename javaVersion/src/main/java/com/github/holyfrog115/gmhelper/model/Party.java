package com.github.holyfrog115.gmhelper.model;

import com.github.holyfrog115.gmhelper.exception.GameRuleException;

import java.util.ArrayList;
import java.util.List;

public class Party {
    private final List<PlayerCharacter> members = new ArrayList<>();

    public Party() {
        System.out.println("Объект класса Party был создан.");
    }

    public Party(PlayerCharacter character) {
        addCharacter(character);
        System.out.println("Объект класса Party был создан.");
    }

    public Party(List<PlayerCharacter> characters) {
        addCharacter(characters);
        System.out.println("Объект класса Party был создан.");
    }

    public void addCharacter(PlayerCharacter character) {
        if (character != null && !members.contains(character)) {
            members.add(character);
        }
    }

    public void addCharacter(List<PlayerCharacter> characters) {
        if (characters == null) {
            return;
        }
        for (PlayerCharacter character : characters) {
            addCharacter(character);
        }
    }

    public void removeCharacter(int index) {
        if (index <= 0) {
            return;
        }
        index--;

        if (index < members.size()) {
            members.remove(index);
        }
    }

    public void removeCharacter(PlayerCharacter character) {
        for (int i = 0; i < members.size(); i++) {
            if (members.get(i) == character) {
                members.remove(i);
                return;
            }
        }
    }

    public int calcAvgLevel() {
        if (members.isEmpty()) {
            return 0;
        }

        int totalLevel = 0;
        for (PlayerCharacter character : members) {
            totalLevel += character.getLevel();
        }
        return totalLevel / members.size();
    }

    public boolean searchCharacter(String name) {
        if (name == null) {
            return false;
        }
        for (PlayerCharacter character : members) {
            if (character.getName().contains(name)) {
                return true;
            }
        }
        return false;
    }

    public boolean searchCharacterByFullName(String name) {
        if (name == null) {
            return false;
        }
        for (PlayerCharacter character : members) {
            if (character.getName().equals(name)) {
                return true;
            }
        }
        return false;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("Участники группы:");
        for (int i = 0; i < members.size(); i++) {
            String name = members.get(i).getName();
            if (name.length() > 32) {
                name = name.substring(0, 32) + "...";
            }
            sb.append("\n")
                    .append(i + 1)
                    .append(". ")
                    .append(name);
        }
        return sb.toString();
    }

    public void distributeReward(Lootable source) {
        if (source == null) {
            return;
        }
        if (members.isEmpty()) {
            throw new GameRuleException("Невозможно распределить награду: в группе нет участников.");
        }

        System.out.print(source.getLootDescription());

        int xpPerMember = source.getXpReward() / members.size();
        int goldPerMember = source.getGoldReward() / members.size();

        System.out.println("Каждому участнику: +" + xpPerMember + " опыта, " + goldPerMember + " золота.");
    }

    public void distributeReward(List<? extends Lootable> sources) {
        if (members.isEmpty()) {
            throw new GameRuleException("Невозможно распределить награду: в группе нет участников.");
        }
        if (sources == null) {
            return;
        }

        int totalXp = 0;
        int totalGold = 0;
        for (Lootable source : sources) {
            if (source != null) {
                System.out.print(source.getLootDescription());
                totalXp += source.getXpReward();
                totalGold += source.getGoldReward();
            }
        }

        int xpPerMember = totalXp / members.size();
        int goldPerMember = totalGold / members.size();

        System.out.println("Каждому участнику: +" + xpPerMember + " опыта, " + goldPerMember + " золота.");
    }
}