
#include <Arduino.h>

#include "led.hpp"

// Constructeur : initialise les pins et la couleur
LED::LED(int idled, int rouge, int vert, int bleu) : rouge_(rouge), vert_(vert), bleu_(bleu) {
    pinMode(rouge_, OUTPUT);
    pinMode(vert_, OUTPUT);
    pinMode(bleu_, OUTPUT);
}

// Méthode pour allumer la LED
void LED::demarrer() {
    digitalWrite(rouge_, HIGH);
    digitalWrite(vert_, HIGH);
    digitalWrite(bleu_, HIGH);
}

// Méthode pour éteindre la LED
void LED::arreter() {
    digitalWrite(rouge_, LOW);
    digitalWrite(vert_, LOW);
    digitalWrite(bleu_, LOW);
}
