#ifndef __CONNECT_HPP__  // Début de la directive de préprocesseur "ifndef", qui évite les inclusions multiples du fichier d'en-tête "Connect.hpp"
#define __CONNECT_HPP__  // Définition du symbole "__CONNECT_HPP__"

class Connect
{
    // Propriétés privées de la classe Connect
    private:
        char* nomWifi_;  // Nom du réseau Wi-Fi
        char* motDePasse_;  // Mot de passe du réseau Wi-Fi

    // Méthodes publiques de la classe Connect
    public:
        // Constructeur par défaut
        Connect();

        // Constructeur avec des paramètres pour initialiser les propriétés nomWifi_ et motDePasse_
        Connect(char* nomWifi, char* motDePasse);

        // Getters pour récupérer les valeurs des propriétés nomWifi_ et motDePasse_
        char* nomWifi() const;
        char* motDePasse() const;

        // Setters pour modifier les valeurs des propriétés nomWifi_ et motDePasse_
        void nomWifi(char*);
        void motDePasse(char*);

        // Méthode pour se connecter au réseau Wi-Fi en utilisant les identifiants fournis
        void connecter(char* nomWifi, char* motDePasse);

};

#endif // Fin de la directive de préprocesseur "ifndef", avec la définition du symbole "__CONNECT_HPP__"

/*
#ifndef __CONNECT_HPP__
#define __CONNECT_HPP__

#include <string>

class Connect
{
    // Propriétés privées de la classe Connect
    private:
        std::string nomWifi_;
        std::string motDePasse_;

    // Méthodes publiques de la classe Connect
    public:
        // Constructeur par défaut
        Connect();

        Connect(const std::string& nomWifi, const std::string& motDePasse);

        // Getters
        const std::string& nomWifi() const;
        const std::string& motDePasse() const;

        // Setters
        void nomWifi(const std::string&);
        void motDePasse(const std::string&);

        // Se connecter au réseau Wi-Fi
        void connecter(const std::string& nomWifi, const std::string& motDePasse);

};

#endif //__CONNECT_HPP___

 */