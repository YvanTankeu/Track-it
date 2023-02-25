#ifndef __CAPTEURDECHOC_HPP__ // Vérifie si la macro __CAPTEURDECHOC_HPP__ n'est pas définie
#define __CAPTEURDECHOC_HPP__ // Définit la macro __CAPTEURDECHOC_HPP__ pour indiquer que ce code a été inclus

#include "Capteur.hpp" // Inclusion du fichier d'en-tête Capteur.hpp

class CapteurDeChoc : public Capteur { // Définition de la classe CapteurDeChoc qui hérite de la classe Capteur
private:
    int idCapteurChoc_; // Identifiant du capteur de choc
    bool etat_; // État du capteur de choc
public:
    CapteurDeChoc(); // Constructeur par défaut
    CapteurDeChoc(int id); // Constructeur prenant en paramètre l'identifiant du capteur

    bool detecterChoc(); // Méthode pour détecter un choc
    int id() const; // Méthode pour obtenir l'identifiant du capteur (const pour indiquer que la méthode ne modifie pas l'état de l'objet)
    void setId(int id); // Méthode pour modifier l'identifiant du capteur
    bool etat() const; // Méthode pour obtenir l'état du capteur (const pour indiquer que la méthode ne modifie pas l'état de l'objet)
    void setEtat(bool etat); // Méthode pour modifier l'état du capteur
};

#endif // Fin de la section de garde.
