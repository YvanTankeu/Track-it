#include <Arduino.h>

// 02 Includes pour la connexion wifi
//#include <WiFi.h>
//#include <WiFiClient.h>

#include "connect.hpp"

// -----------------------------------------------------------------------------------------------------------------------
// -------------------------- Implementation des Fonctions de connect ----------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------

/**
 * @brief Construit un nouvel objet de la classe Connect.
 *
 * @param nomWifi const char* Pointeur vers la chaîne SSID.
 * @param motDePasse const char* Optionel pointeur vers la chaîne mot de passe compris entre ASCII 32 et 126 (décimal).
 */
Connect::Connect(char *nomWifi, char *motDePasse)
    : nomWifi_(nomWifi), motDePasse_(motDePasse) {}

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
void Connect::connecter(char *nomWifi, char *motDePasse)
{
    WiFi.begin(nomWifi, motDePasse);
}
