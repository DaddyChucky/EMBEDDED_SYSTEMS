/*
 * Auteurs: Matis Gregoire, Charles De Lafontaine, Genevieve Pelletier-Mc Duff, Fanilotiana Guy et Ismail Essid
 * Description/Fonctions/Registres > vous referer au .h respectif
*/

#include "controleDEL.h"

ControleDEL::ControleDEL(volatile uint8_t* port, const uint8_t brochePositive, const uint8_t brocheNegative):
	port_(port), brochePositive_(brochePositive), brocheNegative_(brocheNegative)
{};

void ControleDEL::modifierCouleur(const Couleurs& couleur) {
	switch (couleur) {
		case ambre:
			modifierCouleur(verte);
			_delay_ms(DELAI_AMBRE_MS);
			modifierCouleur(rouge);
			_delay_ms(DELAI_AMBRE_MS);
			break;

		case verte:
			*port_ |= 1 << brochePositive_;
			*port_ &= ~(1 << brocheNegative_);
			break;

		case rouge:
			*port_ |= 1 << brocheNegative_;
			*port_ &= ~(1 << brochePositive_);
			break;

		case eteinte:
			*port_ &= ~(1 << brochePositive_ | 1 << brocheNegative_);
			break;
	}
}
