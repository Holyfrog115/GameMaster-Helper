package com.github.holyfrog115.gmhelper.utils;

import java.util.concurrent.ThreadLocalRandom;

public class DiceUtils {
    public static int rollD20() {
        return ThreadLocalRandom.current().nextInt(1, 21);
    }
}
