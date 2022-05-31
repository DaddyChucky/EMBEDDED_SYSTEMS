/*
 * Auteurs: 
 *      Éq. 115 (Charles De Lafontaine & Geneviève Pelletier-Mc Duff);
 *      Éq. 109 (Matis Grégoire);
 *      Éq. 117 (Fanilotiana Guy).
 *
 * 
 * Description:
 *      Cette classe permet de prendre en charge le clavier dans le circuit pour savoir quel bouton a 
 *      ete appuye par l'utilisateur (stocke dans l'attribut bouton). Veuillez noter que la routine 
 *      d'interruptions ISR doit etre ajoutee dans le fichier main.cpp du projet. De plus, la classe a 
 *      ete cree pour le robot du projet final ou le clavier etait connecte aux ports C2 a C7. 
 *      (Rangee = C7 a C5 ; Colonnes = C4 a C2) 
 * 
 * 
 * Fonctions:
 * 		
 *      Clavier();
 *          Constructeur qui permet d'activer les interruptions sur les broches PCINT23:16 (PORTC).
 *          L'attribut bouton est mis a l'etat inactif.
 * 
 * 
 *      void configurerColonnesSorties();
 *          Permet de configurer les colonnes (PC2 a PC4) du clavier en mode sortie et les rangees (PC5 a PC7) en entree.
 *          Seules les interruptions sur les pins en entrees (rangees) sont activees. Pour les pins en sortie (colonnes),
 *          elles sont mises a 1 pour permettre de detecter un signal sur les rangees lors d'un appui.
 * 
 * 
 *      void configurerRangeesSorties();
 *          Permet de configurer les colonnes (PC2 a PC4) du clavier en mode entree et les rangees (PC5 a PC7) en sortie.
 *          Seules les interruptions sur les pins en entrees (colonnes) sont activees. Pour les pins en sortie (rangees),
 *          elles sont mises a 1 pour permettre de detecter un signal sur les colonnes lors d'un appui.
 * 
 * 
 *      void determinerBouton(const volatile uint8_t, const volatile uint8_t);
 *          Permet de determiner quel bouton a ete active par l'utilisateur. Utilise la colonne et rangee actives passees 
 *          en parametres afin de connaitre lequel bouton a ete appuye.
 * 
 * 
 * Registres utilises pour permettre l'utilisation des interruptions sur les pins C2 a C7:
 *              ---> Documentation Atmel : A partir de la page 70 <---
 * 
 *      PCICR (Pin Change Interrupt Control Register) : 
 *          Permet d'activer les interruptions sur les pins du port C en mettant a 1 le bit : PCIE2.
 *          Chaque pin voulue devra etre activee precisement avec le registre PCMSK2.
 * 
 *      PCIFR (Pin Change Interrupt Flag Register) :
 *          Correspond aux flags relies aux interruptions sur les pins activees. 
 *          Pour reinitialiser les flags et permettre de nouvelles interruptions, il faut mettre un 1 au bit : PCIF2.
 * 
 *      PCMSK2 (Pin Change Mask Register 2) :
 *          Permet d'activer les interruptions sur les pins precices parmi celles du port C.
 *          Selon si les colonnes ou les rangees sont en lecture, l'activation des pins sera differente:
 *              -- ACTIVER_INTERRUPTION_RANGEE     (1 << PCINT21) | (1 << PCINT22) | (1 << PCINT23)
 *              -- ACTIVER_INTERRUPTION_COLONNE    (1 << PCINT18) | (1 << PCINT19) | (1 << PCINT20)
 * 
 */

#pragma once
#include "inclusions.h"

enum Bouton {inactif, bouton1, bouton2, bouton4, boutonR, boutonV, boutonC, boutonI, boutonE, boutonDiese };

static const Bouton BOUTONS_COLONNE_1[3] = { bouton1, boutonR, boutonI };
static const Bouton BOUTONS_COLONNE_2[3] = { bouton2, boutonV, boutonE };
static const Bouton BOUTONS_COLONNE_3[3] = { bouton4, boutonC, boutonDiese };

#define COLONNE_1           1
#define COLONNE_2           2
#define COLONNE_3           3
#define RANGEE_1            1
#define RANGEE_2            2
#define RANGEE_3            3
#define NON_DEFINI          0
#define COLONNES_EN_SORTIE  0x1C     // Colonnes en sorties (et mis a 1), rangees en entrees (0b00011100)
#define RANGEES_EN_SORTIE   0xE0     // Rangees en sorties (et mis a 1), colonnes en entrees (0b11100000)

#define ACTIVER_INTERRUPTION_RANGEE     (1 << PCINT21) | (1 << PCINT22) | (1 << PCINT23)
#define ACTIVER_INTERRUPTION_COLONNE    (1 << PCINT18) | (1 << PCINT19) | (1 << PCINT20)


class Clavier 
{
public :
    Clavier();
    void configurerColonnesSorties();
    void configurerRangeesSorties();
    void determinerBouton(const volatile uint8_t, const volatile uint8_t);

    Bouton getBouton() const {
        return bouton;
    }

private:
    Bouton bouton = inactif;
};
