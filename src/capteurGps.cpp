// -----------------------------------------------------------------------------------------------------------------------
// -------------------------- Implementation des Fonctions du capteur gps ----------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------

#include "capteurGps.hpp"
#include <Arduino.h>
#include <TinyGPS++.h>
#define gpsSerial Serial1

// L'objet TinyGPSPlus
TinyGPSPlus gps;

// Constructeurs
CapteurGps::CapteurGps() : Capteur(), idCapteurGps_(0), latitude_(0.0), longitude_(0.0), altitude_(0.0), vitesse_(0.0) {}

CapteurGps::CapteurGps(int idCapteurGps) : Capteur(), idCapteurGps_(idCapteurGps), latitude_(0.0), longitude_(0.0), altitude_(0.0), vitesse_(0.0){}

std::pair<double, double> CapteurGps::getGeolocalisation()
{
    //double vitesse = 0;
    while (gpsSerial.available() > 0)
    {
        if (gps.encode(gpsSerial.read()))
        {
            latitude_ = gps.location.lat();
            longitude_ = gps.location.lng();
            vitesse_ = gps.speed.kmph();
        }
    }
    return std::make_pair(latitude_, longitude_);
}

double CapteurGps::getData()
{
    // Récupérer la latitude et la longitude du capteur GPS
    double latitude = getGeolocalisation().first;
    double longitude = getGeolocalisation().second;

    // Calculer la valeur à retourner (par exemple, la somme de la latitude et de la longitude)
    double value = latitude + longitude;

    return value;
}

// Accesseurs et Mutateurs
int CapteurGps::idCapteurGps() const
{
    return idCapteurGps_;
}

void CapteurGps::idCapteurGps(int idCapteurGps)
{
    idCapteurGps_ = idCapteurGps;
}

double CapteurGps::vitesse() const
{
    return vitesse_;
}

void CapteurGps::vitesse(double vitesse)
{
    vitesse_ = vitesse;
}

double CapteurGps::latitude() const
{
    return latitude_;
}

void CapteurGps::latitude(double latitude)
{
    latitude_ = latitude;
}


double CapteurGps::longitude() const
{
    return longitude_;
}

void CapteurGps::longitude(double longitude)
{
    longitude_ = longitude;
}


