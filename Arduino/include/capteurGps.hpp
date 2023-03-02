#ifndef __CAPTEURGPS_HPP__
#define __CAPTEURGPS_HPP__

#include "capteur.hpp"

class CapteurGps : public Capteur {
    private:
        int idCapteurGps_;
        double latitude_;
        double longitude_;
<<<<<<< HEAD:Arduino/include/capteurGps.hpp
        double vitesse_;
=======
        double altitude_;
        bool etat_;
>>>>>>> parent of fe25186 (Testing des fonctions dans le main):include/capteurGps.hpp
        
    public:
        // Constructeurs
        CapteurGps();
        CapteurGps(int idCapteurGps);

        // calculer la vitesse de l'objet
        double calculerVitesse();

        /**
         * @brief Get the Geolocalisation object
         * 
         * @return  retourne une paire de valeurs de type double, représentant respectivement la latitude et la longitude du capteur GPS. 
         */
        std::pair<double, double> getGeolocalisation();

        //Obtenir l'etat du capteur
        bool etatCapteur();
        
        // Accesseurs et Mutateurs
        int idCapteurGps() const;
        void idCapteurGps(int idCapteurGps);

        double latitude() const;
        void latitude(double latitude);

        double longitude() const;
        void longitude(double longitude);

        double altitude() const;
        void altitude(double altitude);

        bool etat() const;
        void etat(bool etat);
};

#endif