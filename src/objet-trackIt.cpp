// -----------------------------------------------------------------------------------------------------------------------
// -------------------------- Implementation objet-trackIt.hpp -----------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------

#include "objet-trackIt.hpp"

ObjetTrackIt::ObjetTrackIt()
    : idObjet_(0), idCapteurGPS_(0), idCapteurChoc_(0), idLedRGB_(0), idMoteur_(0)
{
    // Constructeur par défaut
}

ObjetTrackIt::ObjetTrackIt(int idObjet, int idCapteurGPS, int idCapteurChoc, int idLedRGB, int idMoteur)
    : idObjet_(idObjet), idCapteurGPS_(idCapteurGPS), idCapteurChoc_(idCapteurChoc), idLedRGB_(idLedRGB), idMoteur_(idMoteur)
{
    // Constructeur prenant en paramètre tous les identifiants
}

// Accesseurs et modificateurs pour l'identifiant de l'objet
int ObjetTrackIt::idObjet() const
{
    return idObjet_;
}

void ObjetTrackIt::setIdObjet(int id)
{
    idObjet_ = id;
}

// Accesseurs et modificateurs pour l'identifiant du capteur GPS
int ObjetTrackIt::idCapteurGPS() const
{
    return idCapteurGPS_;
}

void ObjetTrackIt::setIdCapteurGPS(int id)
{
    idCapteurGPS_ = id;
}

// Accesseurs et modificateurs pour l'identifiant du capteur de choc
int ObjetTrackIt::idCapteurChoc() const
{
    return idCapteurChoc_;
}

void ObjetTrackIt::setIdCapteurChoc(int id)
{
    idCapteurChoc_ = id;
}

// Accesseurs et modificateurs pour l'identifiant de la LED RGB
int ObjetTrackIt::idLedRGB() const
{
    return idLedRGB_;
}

void ObjetTrackIt::setIdLedRGB(int id)
{
    idLedRGB_ = id;
}

// Accesseurs et modificateurs pour l'identifiant du moteur
int ObjetTrackIt::idMoteur() const
{
    return idMoteur_;
}

void ObjetTrackIt::setIdMoteur(int id)
{
    idMoteur_ = id;
}

// Méthodes

void ObjetTrackIt::seConnecterWIFI(const char *ssid, const char *password)
{
    // Code pour se connecter au réseau WiFi
}

void ObjetTrackIt::publier(const char *topic, const char *message)
{
    // Code pour publier un message sur un topic
}

void ObjetTrackIt::souscrire(const char *topic)
{
    // Code pour souscrire à un topic
}

void ObjetTrackIt::envoyerData()
{
    // Code pour envoyer les données (capteurs GPS et de choc) au serveur
}
