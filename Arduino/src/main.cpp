
/***********************************************************************************************************************
 * L'OBJET CONNECTÉ "TRACK-IT" EST UN PROJET INNOVANT VISANT À AMÉLIORER LA SÉCURITÉ ROUTIÈRE EN SURVEILLANT LA VITESSE* 
 * DES BUS EN TEMPS RÉEL, EN LES GÉOLOCALISANT ET EN PERMETTANT L'ARRÊT À DISTANCE DE LEUR MOTEUR EN CAS DE BESOIN.    *
 * CE PROJET A ÉTÉ CONÇU POUR RÉPONDRE À UN BESOIN URGENT DE CONTRÔLE DE LA VITESSE, ÉTANT DONNÉ QUE 30% DES ACCIDENTS *
 *  DE LA ROUTE SONT CAUSÉS PAR UN EXCÈS DE VITESSE. EN METTANT EN ŒUVRE CE SYSTÈME DE SUIVI, NOUS ESPÉRONS RÉDUIRE    *
 *  LE NOMBRE D'ACCIDENTS ET ENCOURAGER LES CONDUCTEURS À ADOPTER UNE CONDUITE PLUS RESPONSABLE.                       *
 ***********************************************************************************************************************/

#ifndef __ARDUINO_H__  // Vérifie si la bibliothèque WiFi101 est déjà incluse ou non
    #include <Arduino.h>  // Si elle n'est pas incluse, l'inclut
#endif 

#include "capteurGps.hpp"
#include "moteur.hpp"
#include "led.hpp"

#define gpsSerial Serial1


//RGB LED 
const int redLED= 4; //red LED connects to digital pin 2
const int greenLED= 3; //green LED connects to digital pin 4
const int blueLED= 2; //blue LED connects to digital pin 7

//Moteur
const int moteurPin = 7;

CapteurGps gpsSensor(1);
Moteur moteur(1, moteurPin);
LED ledRGB(1, redLED, greenLED, blueLED);

double speed;
double longitude;
double latitude;

void setup()
{
  Serial1.begin(9600);
}

void loop()
{
   
    std::pair<double, double> geo = gpsSensor.getGeolocalisation();
    longitude = geo.first;
    latitude = geo.second;
    speed = gpsSensor.vitesse();

    // Afficher les informations sur le moniteur série
    Serial.print("Longitude: ");
    Serial.print(longitude, 6);
    Serial.print(", Latitude: ");
    Serial.print(latitude, 6);
    Serial.print(", Vitesse: ");
    Serial.print(speed, 4);
    Serial.println(F(" KMPH ")); 

    ledRGB.startLight(ledRGB.ROUGE);
    delay(2000);

    ledRGB.startLight(ledRGB.VERT);
    delay(2000);

    ledRGB.startLight(ledRGB.BLEU);

    //moteur.demarrer();
    delay(2000);
    ledRGB.arreter();

    //moteur.arreter();

    //delay(2000);
}

