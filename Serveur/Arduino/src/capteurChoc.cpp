// -----------------------------------------------------------------------------------------------------------------------
// -------------------------- Implementation des Fonctions du capteur de choc --------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------
#ifndef __ARDUINO_H__  // Vérifie si la bibliothèque WiFi101 est déjà incluse ou non
    #include <Arduino.h>  // Si elle n'est pas incluse, l'inclut
#endif
#include "capteurChoc.hpp"

CapteurDeChoc::CapteurDeChoc() : idCapteurChoc_(0), etat_(false) {} // Initialisation des attributs par défaut

CapteurDeChoc::CapteurDeChoc(int id) : idCapteurChoc_(id), etat_(false) {} // Initialisation des attributs avec l'identifiant du capteur

CapteurDeChoc::CapteurDeChoc(int id, int pin) : idCapteurChoc_(id),  pin_(pin) {
    pinMode(pin_, INPUT);
}

bool CapteurDeChoc::detecterChoc() {
    int valeurCapteur = 0; // Variable pour stocker la valeur du capteur
    valeurCapteur = analogRead(pin_);
    if( valeurCapteur =! 0) // Lire la valeur du capteur
        return true; // Si un choc est détecté, retourne true, sinon retourne false
    else
        return false;
}

int CapteurDeChoc::id() const {
    return idCapteurChoc_; // Retourne l'identifiant du capteur
}

void CapteurDeChoc::setId(int id) {
    idCapteurChoc_ = id; // Modifie l'identifiant du capteur
}

bool CapteurDeChoc::etat() const {
    return etat_; // Retourne l'état du capteur
}

void CapteurDeChoc::setEtat(bool etat) {
    etat_ = etat; // Modifie l'état du capteur
}
