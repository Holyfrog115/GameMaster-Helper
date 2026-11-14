package com.github.holyfrog115.gmhelper.model;

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
}