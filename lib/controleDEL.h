/*
 * Auteur: Genevieve Pelletier-Mc Duff, Charles De Lafontaine, Matis Gregoire, Fanilotiana Guy et Ismail Essid
 * 
 * Description: Cette classe permet le controle de la couleur d'une DEL bicolore.
 * 
 * Fonctions:
 * 		
 * 		ControleDEL(volatile uint8_t* port, const uint8_t brochePositive, const uint8_t brocheNegative):
 * 			Constructeur qui prend comme parametres le port sur lequelle la DEL est branchee ainsi que la broche positive
 * 			et negative pour pouvoir controller le sens du courant (ce qui affecte la couleur de la DEL).
 * 
 * 		void modifierCouleur(const Couleurs& couleur):
 * 			Permet de changer l'etat de la DEL, ce qui comprend ambre, verte, rouge et eteinte. Pour la couleur ambre,
 * 			la fonction modifierCouleur(ambre) doit etre reappelee dans une boucle, sinon la DEL apparaitra rouge.
 * 
 */

#include "inclusions.h"

enum Couleurs { ambre, verte, rouge, eteinte };
constexpr uint8_t DELAI_AMBRE_MS = 5;

class ControleDEL {
	volatile uint8_t* port_;
	const uint8_t brochePositive_;
	const uint8_t brocheNegative_;

public:
	ControleDEL(volatile uint8_t*, const uint8_t, const uint8_t);
	void modifierCouleur(const Couleurs&);
};
