
// -----------------------------------------------------------------------------------------------------------------------
// -------------------------- Implementation des Fonctions de connect ----------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------

#include <Arduino.h>

// 02 Includes pour la connexion wifi
//#include <WiFi.h>
//#include <WiFiClient.h>

#include "connect.hpp"
#ifndef __WIFI101_H__  // Vérifie si la bibliothèque WiFi101 est déjà incluse ou non
    #include <WiFi101.h>  // Si elle n'est pas incluse, l'inclut
#endif 

#ifndef __MQTT_H__
        #include <ArduinoMqttClient.h>
#endif // __ARDUINOMQTTCLIENT_H__

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);



String Payload = "{"; // Chaine de caractère qui contiendra le message envoyer de l'objet vers node-red
bool first = false;

String RPCData, PrevData;

const char topic[] = "home/HumTemp";
const char topicTemp[] = "home/temperature";


/**
 * @brief Construit un nouvel objet de la classe Connect.
 *
 * @param nomWifi const char* Pointeur vers la chaîne SSID.
 * @param motDePasse const char* Optionel pointeur vers la chaîne mot de passe compris entre ASCII 32 et 126 (décimal).
 */
Connect::Connect(char *nomWifi, char *motDePasse)
    : nomWifi_(nomWifi), motDePasse_(motDePasse) {}

/*// Constructeur avec des paramètres pour initialiser les propriétés nomWifi_, motDePasse_, host et port
Connect::Connect(char* nomWifi, char* motDePasse,  char* host, uint16_t port) 
    : nomWifi_(nomWifi), motDePasse_(motDePasse), host_(host), port_(port)
{
}*/


/**
 * @brief Retourne le nom actuel associé au réseau.
 *
 * @return char* Pointeur vers la chaîne de caractères contenant le SSID.
 */
char *Connect::nomWifi() const
{
    return nomWifi_;
}

/**
 * @brief Retourne le mot de passe actuel associé au réseau.
 *
 * @return char* Pointeur vers la chaîne de caractères contenant le mot de passe.
 */
char *Connect::motDePasse() const
{
    return motDePasse_;
}

/**
 * @brief Modifie le SSID du réseau.
 *
 * @param nomWifi Pointeur vers la chaîne de caractères contenant le nouveau SSID.
 */
void Connect::nomWifi(char *nomWifi)
{
    nomWifi_ = nomWifi;
}

/**
 * @brief Modifie le mot de passe du réseau.
 *
 * @param motDePasse Pointeur vers la chaîne de caractères contenant le nouveau mot de passe.
 */
void Connect::motDePasse(char *motDePasse)
{
    motDePasse_ = motDePasse;
}

/**
 * @brief Utilisé pour se connecter au réseau WiFi.
 *
 * @param nomWifi Pointeur vers la chaîne de caractères contenant le SSID.
 * @param motDePasse Pointeur vers la chaîne de caractères contenant le mot de passe.
 */
void Connect::connectWiFi(char *nomWifi, char *motDePasse)
{
   //tentative de connexion au réseau WiFi:
    Serial.print("Tentative de connexion au  SSID: ");
    Serial.println(nomWifi);
    while (WiFi.begin(nomWifi, motDePasse) != WL_CONNECTED)
    {
        //échec, réessayer
        Serial.print(".");
        delay(5000);
    }
    Serial.println("Vous êtes connecté au réseau");
    Serial.println();
}

/**
 * @brief Méthode pour se connecter au broker MQTT en utilisant les identifiants fournis
 * @param host Le nom du broker MQTT
 * @param port Le numéro de port sur lequel se connecter
 */
void connectToBroker(const char *host, uint16_t port)
{
    Serial.print("Tentative de connexion au COURTIER MQTT: ");
    Serial.println(host);

    if (!mqttClient.connect(host, port))
    {
        Serial.print("La connexion MQTT a échoué ! Code d'erreur = ");
        Serial.println(mqttClient.connectError());

        while (1)
            ;
    }

    Serial.println("Vous êtes connecté au MQTT BROKER!");
    Serial.println();
}

void envoyerData()
{
    char attributes[200];
    Payload += "}}";
    Payload.toCharArray(attributes, 200);
    
    mqttClient.beginMessage(topic);
    mqttClient.print(attributes);
    mqttClient.endMessage();

    Serial.print("Payload -> ");
    Serial.println(Payload);
    Serial.print("Payload length -> ");
    Serial.println(Payload.length());
}

/*
  Fonctionnalité qui permet de créer la chaine de données a envoyé au broker MQTT
  Pour le moment, cette chaine ne doit pas dépassé un maximum de 100 caractère
*/
// {"ts":1666778909000,"values":{
void appendTimestamps(float value)
{
  first = false;
  Payload = "{\"ts\":";
  Payload += value;
  Payload += ",\"values\":{";
}

//"Temperature":23.169,"Humidite":59.411}}
void appendPayload(String Name, float Val)
{
  if (first)
  {
    Payload += ",";
  }
  Payload += "\"";
  Payload += Name;
  Payload += "\": ";
  Payload += Val;
  first = true;
}
