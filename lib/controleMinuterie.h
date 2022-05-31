/*
 * Auteurs: Matis Gregoire, Charles De Lafontaine, Genevieve Pelletier-Mc Duff, Fanilotiana Guy et Ismail Essid
 * 
 * Description: Cette classe permet de controler les minuteries 0 et 2 de 8 bits de la carte ATMega324a
 * 
 * Fonctions:
 *      *Minuterie 1*
 *      void partirMinuterie1(const uint8_t valeurCompA, const uint8_t valeurCompB, const ModeComp& modeCompA, const ModeComp& modeCompB, const FreqSource& freqSource):
 *          Cette fonction permet de partir la minuterie 0 en lui envoyant une valeur et un mode de comparaison pour le comparateur A et B.
 *          Le paramètre freqSource permet aussi d'indiquer la frequence de l'horloge relativement à celle du CPU.
 * 
 *      void arreterMinuterie1():
 *          Permet d'arrêter la minuterie 0 en mettant TCCR0B à zéro, ce qui équivaut à un freqSource de 0 (desactive).
 * 
 *      void setValeurComp1A(const uint8_t valeur):
 *          Permet de changer la valeur A a laquelle la minuterie 0 doit se comparer pour les interruptions.
 * 
 *      void setValeurComp1B(const uint8_t valeur)
 *          Permet de changer la valeur B a laquelle la minuterie 0 doit se comparer pour les interruptions.
 * 
 * 
 *      *Minuterie 2*
 *      void partirMinuterie2(const uint8_t valeurCompA, const uint8_t valeurCompB, const ModeComp& modeCompA, const ModeComp& modeCompB, const FreqSource& freqSource):
 *          Cette fonction permet de partir la minuterie 2 en lui envoyant une valeur et un mode de comparaison pour le comparateur A et B.
 *          Le paramètre freqSource permet aussi d'indiquer la frequence de l'horloge relativement à celle du CPU.
 * 
 *      void arreterMinuterie2():
 *          Permet d'arrêter la minuterie 2 en mettant TCCR0B à zéro, ce qui équivaut à un freqSource de 0 (desactive).
 * 
 *      void setValeurComp2(const uint8_t valeur):
 *          Permet de changer la valeur A a laquelle la minuterie 2 doit se comparer pour les interruptions.
 * 
 *      void setValeurComp2B(const uint8_t valeur)
 *          Permet de changer la valeur B a laquelle la minuteire 2 doit se comparer pour les interruptions.
 * 
 * Registres utilises:
 *      
 *      TCNTn:  La valeur qui est incrémentee et decrementee par la minuterie interne lors du compte. Elle est mise a zero lorsque la minuterie est partie.
 *      TCCRnA: Permet d'indiquer au microcontroleur le mode de comparaison pour la valeur de comparaison A et B.
 *      TCCRnB: Permet d'indiquer au microcontroleur la fréquence de la minuterie n relativement a celle de CPU.
 *      OCRnA:  Permet d'indiquer au microcontroleur la valeur A a laquelle TCNTn doit etre comparee pour generer une interruption.
 *      OCRNB:  Permet d'indiquer au microcontroleur la valeur B a laquelle TCNTn doit etre comparee pour generer une interruption.
 */

#include "inclusions.h"

enum ModeComp { desactive, basculer, effacer, choisir };
enum FreqSource { arrete, freq1, freq8, freq64, freq256, freq1024 };

class ControleurMinuterie
{
public:
    void partirMinuterie1(const uint8_t, const uint8_t, const ModeComp&, const ModeComp&, const FreqSource&);
    void arreterMinuterie1();
    void setValeurComp1A(const uint8_t);
    void setValeurComp1B(const uint8_t);

    void partirMinuterie2(const uint8_t, const uint8_t, const ModeComp&, const ModeComp&, const FreqSource&);
    void arreterMinuterie2();
    void setValeurComp2A(const uint8_t);
    void setValeurComp2B(const uint8_t);
};
