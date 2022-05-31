/*
 * Auteur: Genevieve Pelletier-Mc Duff, Charles De Lafontaine, Matis Gregoire, Fanilotiana Guy et Ismail Essid
 * 
 * Description: Cette classe permet d'ecrire et de lire dans le EEPROM du microcontroleur ATMega324pa
 * 
 * Fonctions:
 * 		
 * 		EEPROM(uint8_t critereArret, const char tableauLettres[], const uint8_t tailleTableau):
 * 			Constructeur prenant en parametre le critere d'arret pour la lecture du EEPROM, le tableau de caracteres
 * 			a ecrire ainsi que le nombre de caractere a ecrire
 * 
 * 		ecrire():
 * 			Ecrit dans le EEPROM les caracteres contenus dans l'attribut tableauLettres.
 * 
 * 		lire(TransmissionUART UART, ControleDEL led, bool modeDebogage = false):
 * 			Permet de lire les donnees contenues dans le EEPROM et de les afficher par RS232 grace au UART.
 * 			Permet aussi d'activer un mode debogage pour lequel il est possible d'afficher une DEL rouge si jamais
 * 			les donnees lues ne correspondent pas a celles deja en attribut dans tableauLettres.
 * 
 */

#include "RS232.h"
#include "controleDEL.h"

class EEPROM {
	uint8_t			critereArret_;
	uint8_t			tailleTableau_;
	unsigned char 	tableauLettres_[];

public:
	EEPROM(uint8_t critereArret, const char*, const uint8_t tailleTableau);
	void ecrire();
	void lire(TransmissionUART, ControleDEL, bool);
};
