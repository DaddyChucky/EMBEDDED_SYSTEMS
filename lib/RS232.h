/*
 * Auteur: Genevieve Pelletier-Mc Duff, Charles De Lafontaine, Matis Gregoire, Fanilotiana Guy et Ismail Essid
 * 
 * Description: Cette classe permet d'envoyer des donnees via RS232 au microcontroleur ATMega324pa
 * 
 * Fonctions:
 * 		
 * 		TransmissionUART(uint8_t valeurBaudH, uint8_t valeurBaudL, uint8_t formatTrames = (1 << UCSZ01) | (1 << UCSZ00)):
 * 			Constructeur prenant en parametre les debits en bauds (baud rate high/low) et le format des trames,
 *          par defaut a 8 bits, 1 stop bit, none parity
 * 
 * 		ecrire():
 * 			Ecrit dans le EEPROM les caracteres contenus dans l'attribut tableauLettres.
 * 
 * 		lire(TransmissionUART UART, ControleDEL led, bool modeDebogage = false):
 * 			Permet de lire les donnees contenues dans le EEPROM et de les afficher grace au UART.
 * 			Permet aussi d'activer un mode debogage pour lequel il est possible d'afficher un DEL rouge si jamais
 * 			les donnees lues ne correspondent pas a celles deja en attribut dans tableauLettres (mode desactive par defaut).
 * 
 * Registres utilises:
 *      
 *      UBRR0H: Les bits 8-11 du USART qui permettent de definir le debit en bauds.
 *      UBRR0L: Les bits 0-7 du USART qui permettent de definir le debit en bauds.
 *      UCSR0A: Unite de controle pour le registre A du USART.
 *              RXC0: Permet d'effacer le contenu du tampon receveur de donnees (clear buffer).
 *              TXC0: Permet d'effacer le flag relie a la completion d'une transmission (clear TXC0 Flag bit).
 *              UDRE0: Indique si le tampon de transmission est pret a recevoir de nouvelles donnees.
 *              RXEN0: Permet d'activer les interruptions sur RXC0.
 *              TXEN0: Permet d'activer les interruptions sur TXC0.
 *              UCSR0C: Format des trames, par defaut:
 *              UCSZ01: Permet de choisir la taille des caracteres.
 *              UCSZ00: Permet de choisir la taille des caracteres.
 *              USBS0: Selection de stop bits (0 = 1 bit, 1 = 2 bits).
 *              UPM01: Permet de choisir le mode de parite.
 *              UPM00: Permet de choisir le mode de parite.
 *      UCSR0A: Permet de savoir si le registre n'est pas pret a recevoir des donnees.
 *      UDR0: Registre de 8 bits de memoire auquel on transmet une donnee (USART0 I/O Data Register).
 */

#include "inclusions.h"
#define HUIT_BITS_PAS_DE_PARITE_UN_STOP_BIT ((1 << UCSZ01) | (1 << UCSZ00))

class TransmissionUART {

public:
    TransmissionUART(uint8_t, uint8_t, uint8_t);
    void envoyerDonnee(uint8_t);
    uint8_t lireDonnee();
    void envoyerMessage(const char[]);
};
