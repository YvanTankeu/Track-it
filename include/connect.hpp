#ifndef __CONNECT_HPP__  // Début de la directive de préprocesseur "ifndef", qui évite les inclusions multiples du fichier d'en-tête "Connect.hpp"
#define __CONNECT_HPP__  // Définition du symbole "__CONNECT_HPP__"
#ifndef __WIFI101_H__  // Vérifie si la bibliothèque WiFi101 est déjà incluse ou non
    #include <WiFi101.h>  // Si elle n'est pas incluse, l'inclut
#endif 
class Connect
{
    // Propriétés privées de la classe Connect
    private:
        char* nomWifi_;  // Nom du réseau Wi-Fi
        char* motDePasse_;  // Mot de passe du réseau Wi-Fi
        bool wifiConnected_;
        bool brokerConnected_;
        char *host_;
        uint16_t port_;

    // Méthodes publiques de la classe Connect
    public:
        // Constructeur par défaut
        Connect();

        // Constructeur avec des paramètres pour initialiser les propriétés nomWifi_ et motDePasse_
        Connect(char* nomWifi, char* motDePasse);
        
        // Constructeur avec des paramètres pour initialiser les propriétés nomWifi_ et motDePasse_, broker et port
        //Connect(char* nomWifi, char* motDePasse,  char *host, uint16_t port);

        // Getters pour récupérer les valeurs des propriétés nomWifi_ et motDePasse_
        char* nomWifi() const;
        char* motDePasse() const;

        // Setters pour modifier les valeurs des propriétés nomWifi_ et motDePasse_
        void nomWifi(char*);
        void motDePasse(char*);

        // Méthode pour se connecter au réseau Wi-Fi en utilisant les identifiants fournis
        void connectWiFi(char* nomWifi, char* motDePasse);

        bool wifiConnected() const;

        bool brokerConnected() const;

        /**
         * @brief Méthode pour se connecter au broker MQTT en utilisant les identifiants fournis
         * @param host Le nom du broker MQTT
         * @param port Le numéro de port sur lequel se connecter
         */
        void connectToBroker(char *host, uint16_t port);

        void appendPayload(String Name, float Val);

        void appendTimestamps(float value);
        
        String receiveData();

        void envoyerData();

        
};

#endif // Fin de la directive de préprocesseur "ifndef", avec la définition du symbole "__CONNECT_HPP__"