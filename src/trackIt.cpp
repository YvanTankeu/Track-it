// -----------------------------------------------------------------------------------------------------------------------
// -------------------------- Implementation objet-trackIt.hpp -----------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------

#include "trackIt.hpp"

//#include "connect.cpp"
#include "connect.hpp"

#ifndef __WIFI101_H__  // Vérifie si la bibliothèque WiFi101 est déjà incluse ou non
    #include <WiFi101.h>  // Si elle n'est pas incluse, l'inclut
#endif 

#ifndef __ARDUINOMQTTCLIENT_H__
    #include <ArduinoMqttClient.h>
#endif // __ARDUINOMQTTCLIENT_H__

TrackIt::TrackIt(char* nomWifi, char* motDePasse, char* host, uint16_t port) 
  : wifi_(nomWifi, motDePasse), host_(host), port_(port)
{
}

void TrackIt::connectToBrokerByWifi() {
  wifi_.connectWiFi(wifi_.nomWifi(), wifi_.motDePasse());
  wifi_.connectToBroker(host_,port_);
  //connectToBroker(host_, port_);
}

// Méthodes

void TrackIt::seConnecterWIFI(const char *ssid, const char *password)
{
    wifi_.connectWiFi(wifi_.nomWifi(), wifi_.motDePasse());
}

// Définition de la méthode publier
/*void TrackIt::publier(const char *topic, const char *message) {
  mqttClient.connect("TrackIt");  // Se connecter au broker MQTT avec un identifiant unique
  mqttClient.beginMessage(topic, message);  // Publier le message sur le topic spécifié
  mqttClient.endMessage();// Se déconnecter du broker MQTT
}

void TrackIt::souscrire(const char *topic)
{
    // Code pour souscrire à un topic
    mqttClient.subscribe(topic, 1);
}*/

// Accesseurs et modificateurs pour l'identifiant de l'objet
int TrackIt::idObjet() const
{
    return idObjet_;
}

void TrackIt::setIdObjet(int id)
{
    idObjet_ = id;
}

// Accesseurs et modificateurs pour l'identifiant du capteur GPS
int TrackIt::idCapteurGPS() const
{
    return idCapteurGPS_;
}

void TrackIt::setIdCapteurGPS(int id)
{
    idCapteurGPS_ = id;
}

// Accesseurs et modificateurs pour l'identifiant du capteur de choc
int TrackIt::idCapteurChoc() const
{
    return idCapteurChoc_;
}

void TrackIt::setIdCapteurChoc(int id)
{
    idCapteurChoc_ = id;
}

// Accesseurs et modificateurs pour l'identifiant de la LED RGB
int TrackIt::idLedRGB() const
{
    return idLedRGB_;
}

void TrackIt::setIdLedRGB(int id)
{
    idLedRGB_ = id;
}

// Accesseurs et modificateurs pour l'identifiant du moteur
int TrackIt::idMoteur() const
{
    return idMoteur_;
}

void TrackIt::setIdMoteur(int id)
{
    idMoteur_ = id;
}

