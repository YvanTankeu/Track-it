#ifndef __LED_HPP__
#define __LED_HPP__

#include "actionneur.hpp"

// Classe représentant une LED RGB contrôlée par 3 broches distinctes
class LED : public Actionneur {
    private:
        int idled_; // Identifiant de la LED
        int rouge_; // broche de la LED pour la couleur rouge
        int vert_; // broche de la LED pour la couleur verte
        int bleu_; // broche de la LED pour la couleur bleue
    public:
        // Constructeur prenant en paramètres les broches pour chaque couleur
        LED(int idLed, int rouge, int vert, int bleu);

        // Méthode virtuelle de la classe mère à implémenter
        void demarrer() override;

        // Méthode virtuelle de la classe mère à implémenter
        void arreter() override;
};

#endif
