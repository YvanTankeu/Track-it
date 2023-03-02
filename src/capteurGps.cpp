// -----------------------------------------------------------------------------------------------------------------------
// -------------------------- Implementation des Fonctions du capteur gps ----------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------

#include "capteurGps.hpp"
#include <Arduino.h>
#include <TinyGPS++.h>

// L'objet TinyGPSPlus
TinyGPSPlus gps;

// Constructeurs
CapteurGps::CapteurGps() : Capteur(), idCapteurGps_(0), latitude_(0.0), longitude_(0.0), vitesse_(0.0) {}

CapteurGps::CapteurGps(int idCapteurGps) : Capteur(), idCapteurGps_(idCapteurGps), latitude_(0.0), longitude_(0.0), vitesse_(0.0){}

// calculer la vitesse de l'objet
double CapteurGps::calculerVitesse() {
    return gps.speed.kmph();
}

/**
 * @brief Get the Geolocalisation object
 * 
 * @return  retourne une paire de valeurs de type double, représentant respectivement la latitude et la longitude du capteur GPS. 
 */
std::pair<double, double> CapteurGps::getGeolocalisation() {
    latitude_ = gps.location.lat();
    longitude_ = gps.location.lng();
    return std::make_pair(latitude_, longitude_);
}

// Accesseurs et Mutateurs
int CapteurGps::idCapteurGps() const {
    return idCapteurGps_;
}

void CapteurGps::idCapteurGps(int idCapteurGps) {
    idCapteurGps_ = idCapteurGps;
}

double CapteurGps::latitude() const {
    return latitude_;
}

void CapteurGps::latitude(double latitude) {
    latitude_ = latitude;
}

double CapteurGps::longitude() const {
    return longitude_;
}

void CapteurGps::longitude(double longitude) {
    longitude_ = longitude;
}

