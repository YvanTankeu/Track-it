// -----------------------------------------------------------------------------------------------------------------------
// -------------------------- Implementation des Fonctions du capteur de choc --------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------

#include "capteurChoc.hpp"

CapteurDeChoc::CapteurDeChoc() : idCapteurChoc_(0), etat_(false) {} // Initialisation des attributs par défaut

CapteurDeChoc::CapteurDeChoc(int id) : idCapteurChoc_(id), etat_(false) {} // Initialisation des attributs avec l'identifiant du capteur

bool CapteurDeChoc::detecterChoc() {
    int valeurCapteur = 0; // Variable pour stocker la valeur du capteur
    //valeurCapteur = analogRead(pin_);
    if( (valeurCapteur) != 0) // Lire la valeur du capteur
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
