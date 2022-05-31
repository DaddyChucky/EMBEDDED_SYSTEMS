/*
 * Auteurs: Matis Gregoire, Charles De Lafontaine, Genevieve Pelletier-McDuff, Fanilotiana Guy et Ismail Essid
 * Description/Fonctions/Registres > vous referer au .h respectif
*/

#include "boutonPoussoir.h"

BoutonPoussoir::BoutonPoussoir(volatile uint8_t* port, const uint8_t masque, const uint8_t delaiAntiRebondMs):
	port_(port), masque_(masque), delaiAntiRebondMs_(delaiAntiRebondMs)
	{}

bool BoutonPoussoir::estAppuye() const
{
	if (*port_ & masque_) {
		for (uint8_t i = 0; i < delaiAntiRebondMs_; ++i)
			_delay_ms(UN_MS);

		if (*port_ & masque_)
			return true;
	}

	return false;
}
