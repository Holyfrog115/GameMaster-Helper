package com.github.holyfrog115.gmhelper.model;

public class ResistanceDamagePolicy implements DamagePolicy {
    @Override
    public int modifyDamage(int rawDamage) {
        return rawDamage / 2;
    }

    @Override
    public String getPolicyName() {
        return "Сопротивление (x0.5)";
    }
}
