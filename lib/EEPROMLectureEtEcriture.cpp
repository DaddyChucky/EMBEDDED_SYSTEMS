/*
 * Auteurs: Matis Gregoire, Charles De Lafontaine, Genevieve Pelletier-McDuff, Fanilotiana Guy et Ismail Essid
 * Description/Fonctions/Registres > vous referer au .h respectif
*/

#include "EEPROMLectureEtEcriture.h"

EEPROM::EEPROM(uint8_t critereArret, const char tableauLettres[], const uint8_t tailleTableau):
	critereArret_(critereArret), tailleTableau_(tailleTableau)
{
	tableauLettres_[tailleTableau] = *tableauLettres;
}

void EEPROM::ecrire() {
	for (uint16_t i = 0; i < tailleTableau_; ++i)
		eeprom_write_byte((uint8_t*)i, tableauLettres_[i]);
}

void EEPROM::lire(TransmissionUART UART, ControleDEL led, bool modeDebogage = false) {
	// Savoir s'il y a eu un probleme dans la lecture des donnees (afficher une led connectee sur le port A en rouge, utile pour le debogage)
	if (modeDebogage) {
		// La led reste �teinte si toutes les donn�es ont �t� lues
		for (uint16_t i = 0; i < tailleTableau_; ++i) {
			if (eeprom_read_byte((uint8_t*)i) != tableauLettres_[i]) {
				led.modifierCouleur(rouge);
				break;
			}
		}
	}

	else {
		for (uint16_t i = 0; i < tailleTableau_; ++i) {
			if (eeprom_read_byte((uint8_t*)i) == critereArret_)
				break;

			// Envoyer la valeur lue par RS232
			UART.envoyerDonnee(eeprom_read_byte((uint8_t*)i));
		}
	}
}
