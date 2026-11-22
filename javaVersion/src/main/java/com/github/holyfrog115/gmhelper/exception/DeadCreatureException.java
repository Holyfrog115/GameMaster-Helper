package com.github.holyfrog115.gmhelper.exception;

public class DeadCreatureException extends RuntimeException {
    public DeadCreatureException(String creatureName) {
        super("Невозможно применить действие: существо \"" + creatureName + "\" погибло.");
    }
}
