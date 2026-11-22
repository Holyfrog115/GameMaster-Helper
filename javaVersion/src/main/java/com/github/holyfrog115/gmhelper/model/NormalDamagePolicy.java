package com.github.holyfrog115.gmhelper.model;

public class NormalDamagePolicy implements DamagePolicy {
    @Override
    public int modifyDamage(int rawDamage) {
        return rawDamage;
    }

    @Override
    public String getPolicyName() {
        return "Обычный урон (x1)";
    }
}
