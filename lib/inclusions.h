/*
 * Auteur: Genevieve Pelletier-Mc Duff, Charles De Lafontaine, Matis Gregoire, Fanilotiana Guy et Ismail Essid
 * 
 * Description: Permet de definir les inclusions pour l'ensemble des fichiers .h contenues dans la librairie.
 * 
 * Fonctions:
 * 		
 * 		#define F_CPU:
 * 			Definir la frequence du CPU utilise.
 */

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <stdio.h>
