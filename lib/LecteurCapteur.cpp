/*
 * Auteurs: Charles De Lafontaine, Matis Gregoire, Genevieve Pelletier-McDuff, Fanilotiana Guy
 * Description/Fonctions/Registres > vous referer au .h respectif
*/
#include "LecteurCapteur.h"


LectureCapteur LecteurCapteur::lireCapteur(uint8_t select, bool interne)
{
    constexpr uint8_t MASQUE_SELECTION      = 3;
    constexpr uint8_t BITS_SIGNIFICATIFS    = 2;

    PORTA &= ~0x0C ; 
    PORTA |= (select & MASQUE_SELECTION) << BITS_SIGNIFICATIFS;
    LectureCapteur lectureCapteur;
    lectureCapteur.distance = conversionVoltage(interne ? lireCanInterne() : lireCanExterne() << BITS_SIGNIFICATIFS);

    if (lectureCapteur.distance < SEUIL_DANGER ) {
        lectureCapteur.categorie = danger;
    }

    else if (lectureCapteur.distance < SEUIL_ATTENTION) {
        lectureCapteur.categorie = attention;
    }

    else {
        lectureCapteur.categorie = ok;
    }

    return lectureCapteur;
}


float LecteurCapteur::conversionVoltage(uint16_t voltage)
{
    float lecture = -1.0;

    if (voltage < voltagePourDistances[NB_REFERENCES_VOLTAGE - 1].voltage)
        voltage = voltagePourDistances[NB_REFERENCES_VOLTAGE - 1].voltage;

    for (int i = 0; i < NB_REFERENCES_VOLTAGE; i++) {

        if (voltagePourDistances[i].voltage == voltage) {
            lecture = voltagePourDistances[i].distance;
            break;
        }

        else if(voltage > voltagePourDistances[i].voltage) {
            ReferenceDistanceVoltage r1 = voltagePourDistances[i - 1];
            ReferenceDistanceVoltage r2 = voltagePourDistances[i];
            float percent = (float)(voltage - r2.voltage) / (r1.voltage - r2.voltage);
            lecture = r2.distance + (r1.distance - r2.distance) * percent;

            break;
        }
    }
    return lecture;
}


uint16_t LecteurCapteur:: lireCanInterne()
{ 
    PORTA &= ~(1 << PA0) ;
    return convertisseurAnalNum_.lecture(PA1);        
}


uint16_t LecteurCapteur:: lireCanExterne()
{
    constexpr uint8_t DELAI_LECTURE             = 10;
    constexpr uint8_t NB_BOUCLES                = 8;
    constexpr uint8_t BITS_SIGNIFICATIFS_PORT   = 2;
    constexpr uint8_t BITS_SIGNIFICATIFS_DONNEE = 7;
    constexpr uint8_t MASQUE_SELECTION          = 2;

    uint16_t donnee = 0;
    PORTA |= 1 << PA0 ;

    for(uint8_t i = 0 ; i < NB_BOUCLES ;i++) {
        PORTB &= ~MASQUE_CAN_EXTERNE;
        PORTB |= i << BITS_SIGNIFICATIFS_PORT;
        _delay_us(DELAI_LECTURE);
        donnee |=  ((PINB & MASQUE_SELECTION) >> 1) << (BITS_SIGNIFICATIFS_DONNEE - i);        
    }
    
    return donnee;     
}
