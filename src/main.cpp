
/***********************************************************************************************************************
 * L'OBJET CONNECTÉ "TRACK-IT" EST UN PROJET INNOVANT VISANT À AMÉLIORER LA SÉCURITÉ ROUTIÈRE EN SURVEILLANT LA VITESSE*
 * DES BUS EN TEMPS RÉEL, EN LES GÉOLOCALISANT ET EN PERMETTANT L'ARRÊT À DISTANCE DE LEUR MOTEUR EN CAS DE BESOIN.    *
 * CE PROJET A ÉTÉ CONÇU POUR RÉPONDRE À UN BESOIN URGENT DE CONTRÔLE DE LA VITESSE, ÉTANT DONNÉ QUE 30% DES ACCIDENTS *
 *  DE LA ROUTE SONT CAUSÉS PAR UN EXCÈS DE VITESSE. EN METTANT EN ŒUVRE CE SYSTÈME DE SUIVI, NOUS ESPÉRONS RÉDUIRE    *
 *  LE NOMBRE D'ACCIDENTS ET ENCOURAGER LES CONDUCTEURS À ADOPTER UNE CONDUITE PLUS RESPONSABLE.                       *
 ***********************************************************************************************************************/

#ifndef __ARDUINO_H__ // Vérifie si la bibliothèque WiFi101 est déjà incluse ou non
#include <Arduino.h>  // Si elle n'est pas incluse, l'inclut
#endif

#include "capteurGps.hpp"
#include "capteurChoc.hpp"
#include "moteur.hpp"
#include "led.hpp"
#include "trackIt.hpp"
#ifndef __Timer_H__  // Vérifie si la bibliothèque WiFi101 est déjà incluse ou non
    #include "Timer.h" // Si elle n'est pas incluse, l'inclut
#endif

#ifndef __CONNECT_H__  // Vérifie si la bibliothèque WiFi101 est déjà incluse ou non
#include <connect.hpp> // Si elle n'est pas incluse, l'inclut
#endif

#define gpsSerial Serial1

// RGB LED
const int redLED = 4;   // red LED connects to digital pin 2
const int greenLED = 3; // green LED connects to digital pin 4
const int blueLED = 2;  // blue LED connects to digital pin 7

// Moteur
const int moteurPin = 7;

/*const char ssid[] = "HerveStella";
const char pass[] = "Maman123";*/
char ssid[] = "Galaxy";
char pass[] = "12345678";

char BROKER[] = "test.mosquitto.org";
// char BROKER[] = "192.168.1.98";
// char BROKER[] = "192.168.2.32";
uint16_t port = 1883;

CapteurGps gpsSensor(1);
Moteur moteur(1, moteurPin);
CapteurChoc choc(1, 6);
LED ledRGB(1, redLED, greenLED, blueLED);
Connect conn;
// TrackIt trackIt(connect, BROKER, port);

std::pair<double, double> geo;

double speed;
double longitude;
double latitude;
double acceleration;

u_int8_t valMoteur;
String rpcData;
int prevData;

bool lastRpcValue = false;
bool estDemarre = true;

void gestionLumieres() {
  if (speed > 105) {
        ledRGB.startLight(ledRGB.ROUGE);
    }
    else if (speed > 90 && speed < 100) {
        ledRGB.startLight(ledRGB.BLEU);
    }
    else {
        ledRGB.startLight(ledRGB.VERT);
    }
}

void handleRpcData()
{
    rpcData = conn.receiveData();
    // Serial.println(rpcData);

    // Vérifier si la valeur RPC a changé
    if (rpcData == "true" && !lastRpcValue)
    {
        moteur.demarrer();
        lastRpcValue = true;
        estDemarre = true;
    }
    else if (rpcData == "false" && lastRpcValue)
    {
        moteur.arreter();
        lastRpcValue = false;
        estDemarre = false;
         ledRGB.arreter();
    }
    else
    {
        // La valeur RPC n'a pas changé
        // Ne rien faire
    }
}

void obtenirDonneesGPS() {
  // Obtenir les données de géolocalisation
  auto geo = gpsSensor.getGeolocalisation();
  latitude = geo.first;
  longitude = geo.second;
  
  // Obtenir la vitesse et l'accélération
  speed = gpsSensor.vitesse();
  acceleration = gpsSensor.getAcceleration();
  
  // Obtenir la valeur du moteur
  valMoteur = digitalRead(moteur.pinMoteur());
}

void appendSend()
{
    conn.appendTimestamps(random(100000, 120000));
    conn.appendPayload("Longitude", longitude);
    conn.appendPayload("Latitude", latitude);
    conn.appendPayload("Vitesse", speed);
    conn.appendPayload("Acceleration", acceleration);
    conn.appendPayload("Moteur", valMoteur);
    conn.appendPayload("Choc", choc.detecterChoc());
    conn.appendPayload("WiFi", conn.wifiConnected());
    conn.appendPayload("Broker", conn.brokerConnected());

    conn.envoyerData();
}

void initProgram(){
     // Serial.begin(9600);
    gpsSerial.begin(9600);
    conn.connectWiFi(ssid, pass);
    conn.connectToBroker(BROKER, port);
    Serial.println("Bracnhez au test mosquitto");
    moteur.demarrer();
}
void setup()
{
    initProgram();
}

void loop()
{
   // Traiter requete rpc 
   handleRpcData();

    //  si le moteur est démarré ou pas on allumera des light en fonction de ca
    // Gérer les LEDs
    if (estDemarre) {
        gestionLumieres();
    }

    obtenirDonneesGPS();

    /*// Afficher les informations sur le moniteur série
    Serial.print("Longitude: ");
    Serial.print(longitude, 6);
    Serial.print(", Latitude: ");
    Serial.print(latitude, 6);
    Serial.print(", Vitesse: ");
    Serial.print(speed, 4);
    Serial.println(F(" KMPH "));*/

    /*ledRGB.startLight(ledRGB.ROUGE);
    delay(2000);

    ledRGB.startLight(ledRGB.BLEU);
    delay(1000);*/
    /*double latitudes[] = {47.6470067, 47.6481257, 47.6480463, 47.6490024, 47.6473288, 47.6472312, 47.6483718, 47.6488480, 47.6475650, 47.6482878, 47.6491240, 47.6474164, 47.6488933, 47.6496626, 47.6488221, 47.6496855};
    double longitudes[] = {-65.7043328, -65.7028382, -65.7029685, -65.7021123, -65.7041732, -65.7042416, -65.7025290, -65.7021709, -65.7038862, -65.7026242, -65.7020818, -65.7040914, -65.6950071, -65.6938621, -65.6929635, -65.6924206};

    for(int i=0; i<16; i++){
        Serial.print("Latitude : ");
        Serial.print(latitudes[i]);
        Serial.print(" Longitude : ");
        Serial.println(longitudes[i]);

        conn.appendTimestamps(i++);
        conn.appendPayload("Longitude", longitudes[i]);
        conn.appendPayload("Latitude", latitudes[i]);
        conn.appendPayload("Vitesse", speed);

        conn.appendPayload("Moteur", digitalRead(moteur.pinMoteur()));

        conn.appendPayload("Choc", choc.detecterChoc());

        conn.envoyerData();
        delay(5000);
    }*/

    //  appendSend();

    // ledRGB.startLight(ledRGB.VERT);
    // delay(4000);
    if (isTimerReady())
    {
        // Envoyer les données
        appendSend();

        // Redémarrer le minuteur
        startTimer(2000);
    }
}
