/*
 * Auteurs: Matis Gregoire, Charles De Lafontaine, Genevieve Pelletier-Mc Duff, Fanilotiana Guy et Ismail Essid
 * Description/Fonctions/Registres > vous referer au .h respectif
*/

#include "RS232.h"

TransmissionUART::TransmissionUART(uint8_t valeurBaudH, uint8_t valeurBaudL, uint8_t formatTrames) {
    UBRR0H = valeurBaudH;
    UBRR0L = valeurBaudL;

    UCSR0A |= 1 << RXC0 | 1 << TXC0 | 1 << UDRE0;
    UCSR0B |= 1 << RXEN0 | 1 << TXEN0;

    UCSR0C = formatTrames;
}

uint8_t TransmissionUART::lireDonnee() {
    while (!(UCSR0A & (1 << RXC0))) {}
    return UDR0;
}

void TransmissionUART::envoyerDonnee(uint8_t donnee){

    while (!(UCSR0A & (1 << UDRE0))) {}             
    UDR0 = donnee;
}

void TransmissionUART::envoyerMessage(const char msg[])
{
    constexpr char caractereFin = '\0';

    for (uint8_t i = 0; msg[i] != caractereFin; ++i)
    {
        envoyerDonnee(msg[i]);
	}
}
