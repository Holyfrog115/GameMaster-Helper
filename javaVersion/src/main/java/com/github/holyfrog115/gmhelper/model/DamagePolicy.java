package com.github.holyfrog115.gmhelper.model;

public interface DamagePolicy {
    int modifyDamage(int rawDamage);
    String getPolicyName();
}
