
#ifndef __ARDUINO_H__  // Vérifie si la bibliothèque WiFi101 est déjà incluse ou non
    #include <Arduino.h>  // Si elle n'est pas incluse, l'inclut
#endif 

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

void LED::startLight(Couleur couleur){
    // Méthode pour allumer la LED
    switch (couleur) {
        case ROUGE:
            digitalWrite(rouge_, HIGH);
            digitalWrite(vert_, LOW);
            digitalWrite(bleu_, LOW);
            break;
        case VERT:
            digitalWrite(rouge_, LOW);
            digitalWrite(vert_, HIGH);
            digitalWrite(bleu_, LOW);
            break;
        case BLEU:
            digitalWrite(rouge_, LOW);
            digitalWrite(vert_, LOW);
            digitalWrite(bleu_, HIGH);
            break;
        default:
            digitalWrite(rouge_, LOW);
            digitalWrite(vert_, LOW);
            digitalWrite(bleu_, LOW);
            break;
    }
}


// Méthode pour éteindre la LED
void LED::arreter() {
    digitalWrite(rouge_, LOW);
    digitalWrite(vert_, LOW);
    digitalWrite(bleu_, LOW);
}
