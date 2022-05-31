/*
 * Auteurs: 
 *      Éq. 115 (Charles De Lafontaine & Geneviève Pelletier-Mc Duff);
 *      Éq. 109 (Matis Grégoire);
 *      Éq. 117 (Fanilotiana Guy).
 *
 * 
 * Description:
 *      
 *      Cette classe permet de prendre en charge la lecture des capteurs dans notre circuit pour obtenir 
 *      le voltage envoye que ce soit par le CAN interne ou par le CAN externe. De plus, la classe s'occupe 
 *      de convertir directement le voltage recu en distance qui definit par la suite la categorie de l' alerte 
 *      correspondante. 
 * 
 * 
 * Fonctions:
 * 		
 *      LectureCapteur lireCapteur(uint8_t, bool);
 *          Permet de lire les valeurs du Capteurs en speficiant en parametre l'indice du capteur dont on voudrait obtenir
 *          la valeur (soit 0 pour capteur gauche, 1 pour le capteur du milieu et 2 pour le capteur droit). Elle prend 
 *          un bool qui selectionne le CAN par lequel on voudrait transmettre et lire les valeurs du capteur, elle prend 
 *          la valeur true pour le CAN interne et false pour le CAN externe
 *      
 * 
 *      uint16_t lireCanInterne();
 *          Permet de configurer le PORTA pour que la lecture des capteurs se fasse avec le CAN interne
 *          De plus, elle utilise la convertisseur analogique numerique pour retourner le voltage du capteur.
 * 
 *      
 *      uint16_t lireCanInterne();
 *          Permet de configurer le PORTA pour que la lecture des capteurs se fasse avec le CAN externe, en mettant A0 a 1
 *          De plus, elle permet de lire la valeur du voltage du capteur qui se fait bit par bit sur B1 en appliquant un masque 
 *          sur B2 B3 B4 a chacune des 8 iterations de la boucle (pour lire les 8 bits)
 *      
 * 
 */


#pragma once
#define MASQUE_CAN_EXTERNE      0x1C     
#define SEUIL_ATTENTION         50
#define SEUIL_DANGER            20
#define NB_REFERENCES_VOLTAGE   29


#include "inclusions.h"
#include "can.h"


enum CategorieDistance {danger, attention, ok};


struct LectureCapteur 
{
    float distance;
    CategorieDistance categorie;
};


struct ReferenceDistanceVoltage
{
    float distance;
    uint16_t voltage;
};


constexpr ReferenceDistanceVoltage voltagePourDistances[NB_REFERENCES_VOLTAGE] = {
        {10.0, 992},
        {12.5, 816},
        {15.0, 692},
        {17.5, 607},
        {20.0, 548},
        {22.5, 500},
        {25.0, 452},
        {27.5, 417},
        {30.0, 383},
        {32.5, 360},
        {35.0, 337},
        {37.5, 317},
        {40.0, 297},
        {42.5, 281},
        {45.0, 265},
        {47.5, 254},
        {50.0, 245},
        {52.5, 236},
        {55.0, 227},
        {57.5, 220},
        {60.0, 213},
        {62.5, 206},
        {65.0, 200},
        {67.5, 193},
        {70.0, 188},
        {72.5, 182},
        {75.0, 177},
        {77.5, 171},
        {80.0, 167}
    };


class LecteurCapteur
{
public :
    LectureCapteur lireCapteur(uint8_t, bool);
    
private:
    can convertisseurAnalNum_;
    uint16_t lireCanInterne();
    uint16_t lireCanExterne();
    float conversionVoltage(uint16_t);
};
