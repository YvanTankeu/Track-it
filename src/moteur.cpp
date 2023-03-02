#include "moteur.hpp"
#include <Arduino.h>

// Constructeurs
Moteur::Moteur() : idMoteur_(0) {}
Moteur::Moteur(int idMoteur, int pinMoteur) : idMoteur_(idMoteur), pinMoteur_(pinMoteur) {
     pinMode(pinMoteur, OUTPUT);
}

// Méthodes de l'interface Actionneur redéfinies
void Moteur::demarrer() {
// Code pour démarrer le moteur
    digitalWrite(pinMoteur_, HIGH);
}

void Moteur::arreter() {
// Code pour arrêter le moteur
    digitalWrite(pinMoteur_, HIGH);
}

// Accesseurs et Mutateurs
int Moteur::idMoteur() const {
return idMoteur_;
}

int Moteur::pinMoteur() const{
    return pinMoteur_;
}

void Moteur::idMoteur(int idMoteur) {
    idMoteur_ = idMoteur;
}

void Moteur::pinMoteur(int pinMoteur) {
    pinMoteur_ = pinMoteur;
}