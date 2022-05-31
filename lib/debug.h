/*
 * Auteurs: Matis Gregoire, Charles De Lafontaine, Genevieve Pelletier-Mc Duff, Fanilotiana Guy et Ismail Essid
 * 
 * Description: Ce fichier permet d'afficher, en mode débogage, des informations reliées à l'exécution d'un programme.
 * 
 * Fonctions:
 * 		DEBUG_PRINT(msg), soit d'afficher par RS232 un message à la console du simulateur
 */

#include "RS232.h"

#ifdef DEBUG

TransmissionUART transmetteur((uint8_t)0, (uint8_t)0xCF, HUIT_BITS_PAS_DE_PARITE_UN_STOP_BIT);
#define DEBUG_PRINT(msg) transmetteur.envoyerMessage(msg)

#else
#define DEBUG_PRINT(msg) do {} while (0)
#endif
