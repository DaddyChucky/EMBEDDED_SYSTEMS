/*
 * Auteurs: Matis Gregoire, Charles De Lafontaine, Genevieve Pelletier-Mc Duff, Fanilotiana Guy et Ismail Essid
 * 
 * Description: Cette classe permet de controler deux moteurs qui sont branches sur les broches PD4 et PD5 de la carte ATMega324pa.
 * 				Elle gere l'utilisation de la minuterie interne 1 sur 16 bits afin de generer des PWM materiels, ainsi que 
 * 				l'ajustement de la vitesse et du sens des moteurs.
 * 
 * Fonctions:
 * 		ControleMoteurs(volatile uint8_t* portSensMoteur1, uint8_t brocheSensMoteur1, volatile uint8_t* portSensMoteur2, uint8_t brocheSensMoteur2):
 * 				Constructeur pour la classe ControleurMoteurs. Elle prend en parametres le port et la broche ou se situe des points d'entree du pont en H
 * 				pour le sens du moteur (connexion a la broche D du pont H pour la direction du moteur).
 * 
 *      *Moteur1*
 * 			void setVitesseMoteur1(uint8_t vitesse):
 * 				La nouvelle vitesse a laquelle doit operer le moteur1 (entre 0 et 100).
 * 
 * 			void setSensMoteur1(const bool avant):
 * 				Le sens dans le quel le moteur1 doit operer. Si avant est vrai, le courrant passera la broche de sens sera mise a haute tension, sinon elle
 * 				sera mise a basse tension.
 * 
 * 		*Moteur2*
 * 			void setVitesseMoteur2(uint8_t vitesse):
 * 				La nouvelle vitesse a laquelle doit operer le moteur2 (entre 0 et 100).
 * 
 * 			void setSensMoteur2(const bool avant):
 * 				Le sens dans le quel le moteur2 doit operer. Si avant est vrai, le courrant passera la broche de sens sera mise a haute tension, sinon elle
 * 				sera mise a basse tension.
 * 
 * Registres utilises:
 *      TCCR1B: Utilise pour indiquer la frequence de la minuterie 1 relativement a celle du CPU.
 * 		TCCR1C: Mise a 0 pour avoir la valeur de defaut du registre.
 * 		TCCR1A: Utilise pour indiquer le mode de comparaison des valeurs A et B ainsi que pour definir le mode pour le PWM
 * 		OCR1A:  Indique la valeur A a laquelle la minuterie 1 doit comparer son compte afin de generer un PWM sur la broche PD5
 *      OCR1B:  Indique la valeur B a laquelle la minuterie 1 doit comparer son compte afin de generer un PWM sur la broche PD4
 */

#include "inclusions.h"

#define COMPTE_MAX 	254
#define VITESSE_MAX 100
#define VITESSE_MIN 0

class ControleMoteurs
{
	volatile uint8_t* portSensMoteur1_;
	uint8_t brocheSensMoteur1_;
	volatile uint8_t* portSensMoteur2_;
	uint8_t brocheSensMoteur2_;

public:
	ControleMoteurs(volatile uint8_t*, uint8_t, volatile uint8_t*, uint8_t);
	void setVitesseMoteur1(uint8_t);
	void setVitesseMoteur2(uint8_t);
	void setSensMoteur1(const bool);
	void setSensMoteur2(const bool);
};
