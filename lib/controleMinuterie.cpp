/*
 * Auteurs: Matis Gregoire, Charles De Lafontaine, Genevieve Pelletier-Mc Duff, Fanilotiana Guy et Ismail Essid
 * Description/Fonctions/Registres > vous referer au .h respectif
*/

#include "controleMinuterie.h"

void ControleurMinuterie::partirMinuterie1(const uint8_t valeurCompA, const uint8_t valeurCompB, const ModeComp& modeCompA, const ModeComp& modeCompB, const FreqSource& freqSource)
{
    TCNT0 = 0;

    TCCR0A = ((uint8_t)modeCompA << COM0A0) | ((uint8_t)modeCompB << COM0B0);

    TCCR0B = (uint8_t) freqSource;


    setValeurComp1A(valeurCompA);
    setValeurComp1B(valeurCompB);
}

void ControleurMinuterie::arreterMinuterie1()
{
    TCCR0B = 0;
}

void ControleurMinuterie::setValeurComp1A(const uint8_t valeur)
{
    OCR0A = valeur;
}

void ControleurMinuterie::setValeurComp1B(const uint8_t valeur)
{
    OCR0B = valeur;
}

void ControleurMinuterie::partirMinuterie2(const uint8_t valeurCompA, const uint8_t valeurCompB, const ModeComp& modeCompA, const ModeComp& modeCompB, const FreqSource& freqSource)
{
    TCNT2 = 0;

    TCCR2A = ((uint8_t)modeCompA << COM0A0) | ((uint8_t)modeCompB << COM0B0);

    TCCR2B = (uint8_t) freqSource;

    setValeurComp2A(valeurCompA);
    setValeurComp2B(valeurCompB);
}

void ControleurMinuterie::arreterMinuterie2()
{
    TCCR2B = 0;
}

void ControleurMinuterie::setValeurComp2A(const uint8_t valeur)
{
    OCR2A = valeur;
}

void ControleurMinuterie::setValeurComp2B(const uint8_t valeur)
{
    OCR2B = valeur;
}
