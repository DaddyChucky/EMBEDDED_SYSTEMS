/*
 * Auteur: Genevieve Pelletier-Mc Duff, Charles De Lafontaine, Matis Gregoire, Fanilotiana Guy et Ismail Essid
 * 
 * Description: Cette classe permet la gestion de l'antirebond pour un bouton poussoir
 * 
 * Fonctions:
 * 		
 * 		BoutonPoussoir(volatile uint8_t* port, const uint8_t masque, const uint8_t delaiAntiRebondMs):
 * 			Constructeur qui prend en parametres le port sur lequel le bouton poussoir est situe, ainsi
 * 			que le masque qui indique plus precisement sur quelle broche du port. Le dernier parametre est
 * 			le delai voulu en ms pour l'antirebond.
 * 
 * 		bool estAppuye():
 * 			Renvoie vrai si le bouton est appuye en prenant compte de l'antirebond.
 * 
 */

#include "inclusions.h"
#define	UN_MS 1

class BoutonPoussoir {
	volatile const uint8_t* port_;
	const uint8_t masque_;
	const uint8_t delaiAntiRebondMs_;

public:
	BoutonPoussoir(volatile uint8_t*, const uint8_t, const uint8_t);
	bool estAppuye() const;
};
