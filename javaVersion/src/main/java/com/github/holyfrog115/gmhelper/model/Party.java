package com.github.holyfrog115.gmhelper.model;

import java.util.ArrayList;
import java.util.List;

public class Party {
    private List<PlayerCharacter> members = new ArrayList<>();

    public Party(PlayerCharacter character) {
        addCharacter(character);
        System.out.println("Объект класса Party был создан");
    }

    public Party(List<PlayerCharacter> characters) {
        for (PlayerCharacter character : characters) {
            addCharacter(character);
        }
        System.out.println("Объект класса Party был создан");
    }

    public void addCharacter(PlayerCharacter character) {
        if (!members.contains(character)) {
            members.add(character);
        }
    }

    public void removeCharacter(int index) {
        if (index == 0) {
            return;
        }
        index--;

        if (index < members.size()) {
            members.remove(index);
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

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("Участники группы:\n");
        for (int i = 0; i < members.size(); i++) {
            sb.append(i + 1)
                    .append(". ")
                    .append(members.get(i).getName())
                    .append("\n");
        }
        return sb.toString();
    }
}
