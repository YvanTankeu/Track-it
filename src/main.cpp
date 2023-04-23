
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

void blinkLedd()
{
  // Allumer et éteindre la LED 3 fois rapidement
  for (int i = 0; i < 3; i++) {
    ledRGB.startLight(ledRGB.VERT);
    delay(100);
    ledRGB.arreter();
    delay(100);
  }
  
}

void blinkLed(int numBlinks, int onTime, int offTime) {
  for (int i = 0; i < numBlinks; i++) {
    ledRGB.startLight(ledRGB.VERT);
    ledRGB.arreter();
    delay(offTime);
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
void sample()
{
    double latitudes[] = {47.712559, 47.712559, 47.712559, 47.712555, 47.712551, 47.712551, 47.712543, 47.712543, 47.712543, 47.712543, 47.712543, 47.712547, 47.712547, 47.712547, 47.712559, 47.712509, 47.711994, 47.711292, 47.710911, 47.710625, 47.710247, 47.709839, 47.70945, 47.709019, 47.708485, 47.70792, 47.707451, 47.707054, 47.706421, 47.705795, 47.70507, 47.704475, 47.703617, 47.70232, 47.645962, 47.645512, 47.645172, 47.645218, 47.645443, 47.645981, 47.647011, 47.679523, 47.705101, 47.706348, 47.707458, 47.707954, 47.708122, 47.708508, 47.708961, 47.709351, 47.709709, 47.710121, 47.710541, 47.710842, 47.710953, 47.711113, 47.711803, 47.712437};
    double longitudes[] = {-65.706551, -65.706551, -65.706551, -65.706543, -65.706543, -65.706551, -65.706551, -65.706551, -65.706551, -65.706551, -65.706558, -65.706573, -65.706573, -65.706573, -65.70649, -65.706421, -65.706268, -65.706108, -65.706482, -65.707703, -65.709282, -65.711006, -65.712646, -65.714363, -65.716202, -65.717812, -65.719002, -65.719322, -65.718475, -65.717194, -65.716194, -65.715614, -65.71479, -65.713593, -65.699287, -65.699425, -65.700211, -65.701241, -65.702072, -65.702347, -65.702248, -65.700638, -65.716026, -65.71666, -65.71701, -65.717293, -65.71714, -65.716026, -65.71447, -65.712914, -65.711357, -65.709625, -65.707909, -65.706635, -65.706154, -65.705963, -65.706108, -65.706268};
    double vitesses[] = {0.02, 0.02, 0.04, 0.04, 0.07, 0.02, 0.06, 0.13, 0.07, 0.02, 0.61, 0.15, 0.09, 0.17, 5.06, 15.41, 38.08, 36.39, 36.97, 59.15, 69.64, 69.64, 65.86, 75.1, 76.3, 63.28, 42.93, 33.85, 56.62, 62.84, 51.69, 35.5, 76.23, 94.54, 21.63, 35.1, 38.84, 38.84, 34.76, 38.35, 74.82, 99.88, 86.49, 71.6, 52.54, 7.82, 26.26, 61.15, 66.76, 61.86, 66.67, 72.75, 66.93, 40.26, 1.87, 24.45, 46.36, 19.58};

    unsigned long tempsDernierEnvoi = 0;
    unsigned long intervalleEnvoi = 5000; // 2 secondes

int i = 0;

while (i < 50)
{
    handleRpcData(); // Traitement de la requête
     conn.appendTimestamps(1000000);
     conn.appendPayload("Longitude", longitudes[i]);
     conn.appendPayload("Latitude", latitudes[i]);
     conn.appendPayload("Vitesse", vitesses[i]);
     conn.appendPayload("Acceleration", acceleration);
     conn.appendPayload("Moteur", valMoteur);
     conn.appendPayload("Choc", choc.detecterChoc());
     conn.appendPayload("WiFi", conn.wifiConnected());
     conn.appendPayload("Broker", conn.brokerConnected());
    
    
     // Vérifier si suffisamment de temps s'est écoulé depuis le dernier envoi
     if (millis() - tempsDernierEnvoi >= intervalleEnvoi)
     {
         conn.envoyerData();
         ledRGB.blink(100, ledRGB.BLEU);

         // Mettre à jour le temps du dernier envoi
         tempsDernierEnvoi = millis();
         i++; // Passer à la prochaine donnée à envoyer
         
     }
}

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

    //sample();
    if (isTimerReady())
    {
        // Envoyer les données
        appendSend();

        // Redémarrer le minuteur
        startTimer(2000);
    }
}
