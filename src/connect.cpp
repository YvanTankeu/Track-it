
// -----------------------------------------------------------------------------------------------------------------------
// -------------------------- Implementation des Fonctions de connect ----------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------

#include <Arduino.h>
#include "connect.hpp"

#ifndef __MQTT_H__
        #include <ArduinoMqttClient.h>
#endif // __ARDUINOMQTTCLIENT_H__

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

String Payload = "{"; // Chaine de caractère qui contiendra le message envoyer de l'objet vers node-red
bool first = false;

const char topic[] = "trackIt/data";

/**
 * @brief Construit un nouvel objet de la classe Connect.
 *
 * @param nomWifi const char* Pointeur vers la chaîne SSID.
 * @param motDePasse const char* Optionel pointeur vers la chaîne mot de passe compris entre ASCII 32 et 126 (décimal).
 */
Connect::Connect(char *nomWifi, char *motDePasse)
    : nomWifi_(nomWifi), motDePasse_(motDePasse) {}

Connect::Connect()
 {}

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
    wifiConnected_ = true;
    Serial.println("Vous êtes connecté au réseau");
    Serial.println();
}

void Connect::connectToBroker(char *host, uint16_t port)
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
    brokerConnected_ = true;
    Serial.println("Vous êtes connecté au MQTT BROKER!");
    Serial.println();

    // Abonnement à un sujet :
    Serial.print("Abonnement au topic : ");
    Serial.println(topic);
    Serial.println();

    mqttClient.subscribe(topic);
}

void Connect::envoyerData()
{
    // Ajoute une accolade fermante à la fin de la chaîne de caractères Payload
    Payload += "}}";

    // Convertit la chaîne de caractères Payload en un tableau de caractères attributes de taille 200
    char attributes[200];
    Payload.toCharArray(attributes, 200);
    
    // Envoie le message contenant les données au serveur MQTT
    mqttClient.beginMessage(topic);
    mqttClient.print(attributes);
    mqttClient.endMessage();

    // Affiche la longueur et le contenu de la chaîne de caractères Payload à des fins de débogage
    Serial.print("Payload -> ");
    Serial.println(Payload);
    Serial.print("Payload length -> ");
    Serial.println(Payload.length());
}


String Connect::receiveData() {
    // Vider la chaîne de caractères avant de recevoir le message
  String valeurRPCString = "";
  int messageSize = mqttClient.parseMessage();
  if (messageSize>1) {
    // Réception d'un message, affichage du sujet et du contenu
    Serial.print("Message reçu sur le topic '");
    Serial.print(mqttClient.messageTopic());
    Serial.print("', longueur ");
    Serial.print(messageSize);
    Serial.print(" octets : ");
    
    // Affichage du contenu du message
    while (mqttClient.available()) {
      // lire un caractère dans le message MQTT
      char c = mqttClient.read();
      valeurRPCString += c;
    }
    Serial.println(valeurRPCString);
  }
  return valeurRPCString;
}

bool Connect::wifiConnected() const
{
    return wifiConnected_;
}

bool Connect::brokerConnected() const
{
    return brokerConnected_;
}

// {"ts":1666778909000,"values":{
void Connect::appendTimestamps(float value)
{
  first = false;
  Payload = "{\"ts\":";
  Payload += value;
  Payload += ",\"values\":{";
}

//"Temperature":23.169,"Humidite":59.411}}
void Connect::appendPayload(String Name, float Val)
{
  if (first)
  {
        Payload += ",";
  }
  Payload += "\"";
  Payload += Name;
  Payload += "\": ";

  // convertir Val en un nombre à virgule flottante
  String ValStr = String(Val, 6);

  // extraire les six chiffres après la virgule
  int dotIndex = ValStr.indexOf('.');
  String ValAfterDot = ValStr.substring(dotIndex + 1);
  while (ValAfterDot.length() < 6)
  {
        ValAfterDot += '0';
  }

  // concaténer le résultat dans Payload
  Payload += ValStr.substring(0, dotIndex + 1);
  Payload += ValAfterDot;

  first = true;
}
