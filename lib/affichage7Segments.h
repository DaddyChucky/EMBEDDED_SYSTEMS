/*
 * Auteurs: Charles De Lafontaine, Genevieve Pelletier-Mc Duff, Matis Gregoire, Fanilotiana Guy et Ismail Essid
 * 
 * Description: Cette classe permet d'afficher et de réinitialiser les 4 panneaux 7 segments.
 * 
 * Fonctions:
 * 		
 * 		Panneau7Segments(volatile uint8_t*, const uint8_t, volatile uint8_t*, const uint8_t):
 * 			Constructeur qui prend comme parametres le port et la broche d'activation, de même que le
 *			port et la broche de réinitialisation.
 * 
 * 		void afficherValeur(const uint8_t):
 * 			Permet d'afficher une valeur hexadécimale sur un tableau 7 segments en particulier.
 * 
 *      void reinitialiserPanneauxPort():
 *          Permet de réinitialiser et de fermer un panneau 7 segments en particuliers.
 *
 *      CouplePanneaux(Panneau7Segments, Panneau7Segments):
 *          Désigne un couple de panneaux (soit le couple gauche ou celui de droite).
 *          Permet de manipuler les deux panneaux en même temps avec les mêmes fonctions décrites précédemment.
 *
 */
#pragma once
#define DELAI_5_MS 5

#include "inclusions.h"

class Panneau7Segments 
{
public:
	Panneau7Segments(volatile uint8_t*, const uint8_t, volatile uint8_t*, const uint8_t);

    void afficherValeur(const uint8_t);
    void reinitialiserPanneauxPort();

private:
    volatile uint8_t*   portActivation_;
    uint8_t             brocheActivation_;
    volatile uint8_t*   portDesactivation_;
    uint8_t             brocheReinitialisation_;
};


class CouplePanneaux
{
public:
    CouplePanneaux(Panneau7Segments, Panneau7Segments);

    void afficherValeur(uint8_t nombre);
    void reinitialiserPanneauxPort();

private:
    Panneau7Segments panneauGauche_;
    Panneau7Segments panneauDroit_;
};
