/*
 * Auteurs: Charles De Lafontaine, Matis Gregoire, Genevieve Pelletier-McDuff, Fanilotiana Guy
 * Description/Fonctions/Registres > vous referer au .h respectif
*/
#include "Clavier.h"


Clavier::Clavier(){
    cli();

    configurerRangeesSorties();

    PCMSK2 = ACTIVER_INTERRUPTION_COLONNE;
    PCIFR |= 1 << PCIF2;
    PCICR |= 1 << PCIE2;

    sei();
}


void Clavier::determinerBouton(const volatile uint8_t colonneActive, const volatile uint8_t rangeeActive)
{
    switch (colonneActive){
        case(COLONNE_1):
            bouton = BOUTONS_COLONNE_1[rangeeActive - 1];
            break;
        
        case(COLONNE_2):
            bouton = BOUTONS_COLONNE_2[rangeeActive - 1];
            break;

        case(COLONNE_3):
            bouton = BOUTONS_COLONNE_3[rangeeActive - 1];
            break;
        default:
            bouton = inactif;
            break;
    }
}


void Clavier::configurerColonnesSorties()
{ 
    DDRC    = COLONNES_EN_SORTIE;  
    PORTC   = COLONNES_EN_SORTIE;
}


void Clavier::configurerRangeesSorties()
{
    DDRC    = RANGEES_EN_SORTIE; 
    PORTC   = RANGEES_EN_SORTIE;
}
