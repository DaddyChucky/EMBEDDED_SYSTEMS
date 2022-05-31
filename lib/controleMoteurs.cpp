/*
 * Auteurs: Matis Gregoire, Charles De Lafontaine, Genevieve Pelletier-Mc Duff, Fanilotiana Guy et Ismail Essid
 * Description/Fonctions/Registres > vous referer au .h respectif
*/

#include "controleMoteurs.h"

ControleMoteurs::ControleMoteurs(volatile uint8_t* portSensMoteur1, uint8_t brocheSensMoteur1, volatile uint8_t* portSensMoteur2, uint8_t brocheSensMoteur2):
	portSensMoteur1_(portSensMoteur1),
	brocheSensMoteur1_(brocheSensMoteur1),
	portSensMoteur2_(portSensMoteur2),
	brocheSensMoteur2_(brocheSensMoteur2)
{
	TCCR1B = 1 << CS11;
	TCCR1C = 0;
	TCCR1A = 1 << WGM10;
	setVitesseMoteur1(0);
	setVitesseMoteur2(0);
}

void ControleMoteurs::setVitesseMoteur1(uint8_t vitesse)
{
	vitesse = vitesse <= VITESSE_MAX ? vitesse : VITESSE_MAX;
	OCR1A	= COMPTE_MAX * vitesse / 100;

	if (vitesse > 0)
		TCCR1A |= (1 << COM1A1);
	else
    {
		TCCR1A &= ~(1 << COM1A1);
        PORTD &= ~(1 << PD4);
    }
}

void ControleMoteurs::setVitesseMoteur2(uint8_t vitesse)
{
	vitesse = vitesse <= VITESSE_MAX ? vitesse : VITESSE_MAX;
	OCR1B = COMPTE_MAX * vitesse / 100;

	if (vitesse > 0)
	{
		TCCR1A |= (1 << COM1B1);
	}
	else
	{
		TCCR1A &= ~(1 << COM1B1);
		PORTD &= ~(1 << PD5);
	}
		
}

void ControleMoteurs::setSensMoteur1(const bool avant)
{
	if (avant)
		*portSensMoteur1_ |= (1 << brocheSensMoteur1_);
	else
		*portSensMoteur1_ &= ~(1 << brocheSensMoteur1_);
}

void ControleMoteurs::setSensMoteur2(const bool avant)
{
	if (avant)
		*portSensMoteur2_ |= (1 << brocheSensMoteur2_);
	else
		*portSensMoteur2_ &= ~(1 << brocheSensMoteur2_);
}
