/*
 * Auteurs: Charles De Lafontaine, Matis Gregoire, Genevieve Pelletier-McDuff, Fanilotiana Guy
 * Description/Fonctions/Registres > vous referer au .h respectif
*/
#include "affichage7Segments.h"


Panneau7Segments::Panneau7Segments(volatile uint8_t* portActivation, const uint8_t brocheActivation, volatile uint8_t* portDesactivation, const uint8_t brocheReinitialisation):
    portActivation_(portActivation), brocheActivation_(brocheActivation), portDesactivation_(portDesactivation), brocheReinitialisation_(brocheReinitialisation)
{};

void Panneau7Segments::afficherValeur(const uint8_t nombre)
{
    *portDesactivation_ &= ~(1 << brocheReinitialisation_);
    *portActivation_ |= 1 << brocheActivation_;
    PORTA = nombre << 4;
    _delay_ms(DELAI_5_MS);  // Pour laisser le temps d'afficher la valeur avant de fermer la bascule
    *portActivation_ &= ~(1 << brocheActivation_);
}

void Panneau7Segments::reinitialiserPanneauxPort() 
{
    *portDesactivation_ = 1 << brocheReinitialisation_;
}

CouplePanneaux::CouplePanneaux(Panneau7Segments panneauGauche, Panneau7Segments panneauDroit):
    panneauGauche_(panneauGauche), panneauDroit_(panneauDroit)
{}

void CouplePanneaux::afficherValeur(uint8_t nombre)
{
    panneauGauche_.afficherValeur(nombre >> 4);
    panneauDroit_.afficherValeur((nombre << 4) >> 4);
}

void CouplePanneaux::reinitialiserPanneauxPort()
{
    // Un seul port par couple de panneaux, inutile de désactiver pour le panneau de droite
    panneauGauche_.reinitialiserPanneauxPort();
}
