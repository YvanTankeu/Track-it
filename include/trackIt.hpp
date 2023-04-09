#ifndef __OBJET_TRACKIT_HPP__ // Vérifie si la macro OBJET_TRACKIT_HPP n'est pas définie
#define __OBJET_TRACKIT_HPP__ // Définit la macro OBJET_TRACKIT_HPP pour indiquer que ce code a été inclus

#include "capteurChoc.hpp" // Inclusion du fichier d'en-tête CapteurDeChoc.hpp
#include "connect.hpp"
#include <ArduinoMqttClient.h>
#include <WiFi101.h>
#include <SPI.h>


class TrackIt
{
    // Définition de la classe TrackIt
private:
    int idObjet_;       // Identifiant de l'objet
    int idCapteurGPS_;  // Identifiant du capteur GPS
    int idCapteurChoc_; // Identifiant du capteur de choc
    int idLedRGB_;      // Identifiant de la LED RGB
    int idMoteur_;      // Identifiant du moteur
    Connect wifi_;
    char* host_;
    uint16_t port_;

public:
   
    TrackIt(Client &client, const char *server, int port); // Constructeur avec client mqtt

    TrackIt(char* nomWifi, char* motDePasse, char* host, uint16_t port);
    void connectToBrokerByWifi();

    // Accesseurs et modificateurs pour l'identifiant de l'objet
    int idObjet() const;
    void setIdObjet(int id);

    // Accesseurs et modificateurs pour l'identifiant du capteur GPS
    int idCapteurGPS() const;
    void setIdCapteurGPS(int id);

    // Accesseurs et modificateurs pour l'identifiant du capteur de choc
    int idCapteurChoc() const;
    void setIdCapteurChoc(int id);

    // Accesseurs et modificateurs pour l'identifiant de la LED RGB
    int idLedRGB() const;
    void setIdLedRGB(int id);

    // Accesseurs et modificateurs pour l'identifiant du moteur
    int idMoteur() const;
    void setIdMoteur(int id);

    // Méthodes
    /**
     * @brief Méthode pour se connecter au réseau WiFi
     * @param ssid Le nom du réseau WiFi
     * @param password Le mot de passe du réseau WiFi
     */
    void seConnecterWIFI(const char *ssid, const char *password);

    /**
     * @brief Méthode pour publier un message sur un topic
     * @param topic Le nom du topic sur lequel publier le message
     * @param message Le message à publier
     */
    void publier(const char *topic, const char *message);

    /**
     * @brief Méthode pour souscrire à un topic
     * @param topic Le nom du topic auquel souscrire
     */
    void souscrire(const char *topic);

    /**
     * @brief Méthode pour envoyer les données (capteurs GPS et de choc) au serveur
     */
    void envoyerData();
};

#endif // Fin de la section de garde.
