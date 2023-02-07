
/***********************************************************************************************************************
 * L'OBJET CONNECTÉ "TRACK-IT" EST UN PROJET INNOVANT VISANT À AMÉLIORER LA SÉCURITÉ ROUTIÈRE EN SURVEILLANT LA VITESSE* 
 * DES BUS EN TEMPS RÉEL, EN LES GÉOLOCALISANT ET EN PERMETTANT L'ARRÊT À DISTANCE DE LEUR MOTEUR EN CAS DE BESOIN.    *
 * CE PROJET A ÉTÉ CONÇU POUR RÉPONDRE À UN BESOIN URGENT DE CONTRÔLE DE LA VITESSE, ÉTANT DONNÉ QUE 30% DES ACCIDENTS *
 *  DE LA ROUTE SONT CAUSÉS PAR UN EXCÈS DE VITESSE. EN METTANT EN ŒUVRE CE SYSTÈME DE SUIVI, NOUS ESPÉRONS RÉDUIRE    *
 *  LE NOMBRE D'ACCIDENTS ET ENCOURAGER LES CONDUCTEURS À ADOPTER UNE CONDUITE PLUS RESPONSABLE.                       *
 ***********************************************************************************************************************/

#include <Arduino.h>
#include <TinyGPSPlus.h>

#define gpsSerial Serial1

// L'objet TinyGPSPlus
TinyGPSPlus gps;

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" Vitesse: ")); 
  if (gps.speed.isValid()){
    Serial.print(gps.speed.kmph(), 2);
    Serial.print(F("KMPH ")); 
  }
  else
    Serial.print(F("INVALID"));

  Serial.println();
}

void setup()
{
 Serial.begin(9600);
 gpsSerial.begin(9600);
}

void loop()
{
  // Cette esquisse affiche des informations chaque fois qu'une nouvelle phrase est correctement encodée.
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();
  delay(1000);
}

