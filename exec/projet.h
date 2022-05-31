#pragma once

#include "LecteurCapteur.h"
#include "constantes.h"
#include "Clavier.h"

#include "affichage7Segments.h"
#include "RS232.h"
#include "controleMoteurs.h"


namespace global {
    TransmissionUART    transmetteur((uint8_t)0, (uint8_t)0x33, HUIT_BITS_PAS_DE_PARITE_UN_STOP_BIT);
    Clavier             clavier{};
};


struct LectureTroisCapteurs
{
    LectureCapteur lectureCapteurGauche;
    LectureCapteur lectureCapteurCentre;
    LectureCapteur lectureCapteurDroite;
};


class Robot
{
public:
    Robot() : 
        panExtGauche(Panneau7Segments(&PORTB, PB5, &PORTB, PB7)),
        panGauche(Panneau7Segments(&PORTB, PB6, &PORTB, PB7)),
        panDroite(Panneau7Segments(&PORTC, PC0, &PORTD, PD7)),
        panExtDroite(Panneau7Segments(&PORTC, PC1, &PORTD, PD7)),
        panneauxGauche(CouplePanneaux(panExtGauche, panGauche)),
        panneauxDroite(CouplePanneaux(panDroite, panExtDroite)),
        controleurMoteurs(ControleMoteurs(&PORTD, PORTD6, &PORTD, PORTD3)),
        manoeuvreAEffectuer(aucune)
    
    {}

    void setVitesseMoteurs(const int8_t, const int8_t);
    void afficherVitessePanneaux7Segments(const uint8_t, const uint8_t);
    void reinitialiserClavier();
    void manoeuvre1();
    void manoeuvre2();
    void manoeuvre3();
    void manoeuvre4();
    void manoeuvre5();
    void fermerPanneaux7Segments();
    void affichageDetection(const LectureTroisCapteurs&, const ModeManoeuvre&);
    void faireManoeuvre(const ModeManoeuvre&);
    void executer();

private:
    Panneau7Segments        panExtGauche;
    Panneau7Segments        panGauche;
    Panneau7Segments        panDroite;
    Panneau7Segments        panExtDroite;
    CouplePanneaux          panneauxGauche;
    CouplePanneaux          panneauxDroite;
    ControleMoteurs         controleurMoteurs;
    LecteurCapteur          lecteurCapteur;
    LecteurCapteur          lecteur;
    ModeManoeuvre           manoeuvreAEffectuer;
    LectureTroisCapteurs    ancienneLectures;
};
