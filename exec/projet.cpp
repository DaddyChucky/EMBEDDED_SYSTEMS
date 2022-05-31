/*
 * Auteurs: Équipe 109-115-117;
 *      Éq. 115 (Charles De Lafontaine & Geneviève Pelletier-Mc Duff);
 *      Éq. 109 (Matis Grégoire);
 *      Éq. 117 (Fanilotiana Guy).
 *
 *
 * Description:
 *      Robot qui détecte des obstacles et qui effectue des manoeuvres d'évitement.
 *      Projet final :: INF1900 - Cours de projet initial de système embarqué.
 *
 *
 * Inclusions:
 *      Pour que notre robot puisse fonctionner correctement, il est nécessaire de téléverser sur SimulIDE 
 *      le circuit <circuit.simu> compris à l'intérieur du répertoire <projet/exec/>.
 *      * La librairie contenue dans <projet/lib/> doit être compilée avant la compilation de ce fichier.
 *
 * Machine à état: ModeOperation
 * 
 *  État présent        État prochain       Entrée (bouton-poussoir sur D2)      Sortie
 *  demarrage           detection                           X                    Affichage RS-232, panneaux 7 segments et moteurs
 *  detection           detection                       non-appuyé               Affichage RS-232
 *  detection           manoeuvre                         appuyé                 Affichage RS-232
 *  manoeuvre           detection                           X                    Affichage RS-232, panneaux 7 segments et moteurs
 * 
 * 
 *  Registres et ports:
 *      TCCR0B: Timer/Counter Control Register B.
 *          Registre de contrôle auquel nous ajoutons un prescaler de 256.
 *              CS02: Prescaler de 256.
 * 
 *      TCNT0:  Timer Counter 0.
 *          Compteur pour le Timer 0. Nous commençons à compter à partir de 0.
 * 
 *      TIMSK0: Timer/Counter Interrupt Mask Register.
 *          TOIE0: Timer/Counter 0 Overflow Interrupt Enable.
 *              Nous activons les interruptions lorsque la minuterie déborde.
 *      
 *      TIFR0: Timer/Counter 0 Interrupt Flag Register.
 *          TOV0: Timer/Counter 0 Overflow Flag.
 *              Nous nous assurons que le drapeau est réinitialisé avant de commencer le programme
 *              en écrivant un 1 logique à la position du drapeau.
 * 
 *      EIMSK: External Interrupt Mask Register.
 *          INT0: Activer les interruptions externes pour INT0 (D2).
 * 
 *      EICRA: External Interrupt Control Register A.
 *          ISC01: Nous activons les interruptions de INT0 au front descendant.
 * 
 *      EIFR: Enable Interrupt Flag Register.
 *          INTF0: Permet d'activer la prochaine interruption en réinitialisant le drapeau.
 *
 *      PCMSK2: Pin Change Mask Register 2.
 *          Active ou désactive les interruptions sur les broches du port C.
 * 
 *      PCIFR: Pin Change Interrupt Flag Register.
 *          PCIF2: Permet d'activer la prochaine interruption en réinitialisant le drapeau.
 * 
 *
 *  Identifications matérielles (broches I/O):
 *      Sorties:
 *          -> PORTA :: PA0, PA2 à PA7.
 *          -> PORTB :: PB0, PB2 à PB7.
 *          -> PORTC :: PC0, PC1.
 *          -> PORTD :: PD3 à PD7.
 *
 *      Entrées:
 *          -> PORTA :: PA1.
 *          -> PORTB :: PB1.
 *          -> PORTD :: PD0 à PD2.
 *
 *      ** PORTC :: PC2 à PC7 alternent entre les modes sortie et entree pour lire le bon bouton active du clavier.
 */


#include "projet.h"


volatile uint8_t        nFoisApppuye                        = 0;
volatile uint8_t        nOverflows                          = 0;
volatile uint8_t        nSecondes                           = 0;
volatile uint8_t        nMinutes                            = 0;
volatile uint8_t        drapeau1                            = 0; 
volatile uint8_t        drapeau2                            = 0; 
volatile uint8_t        drapeau3                            = 0; 
volatile uint8_t        drapeau4                            = 0; 
volatile float          nCentiemes                          = 0;
volatile float          fractionsSecondesEcoulees           = 0;
volatile uint8_t        frequenceLectureCapteurs            = FREQUENCE_BOUTON_1;
volatile bool           estDecimal                          = false;
volatile bool           estLectureDesCapteursInterne        = true;
volatile bool           estAppuyeBoutonPoussoir             = false;
volatile bool           afficher                            = true;
volatile Bouton         boutonPrecedent                     = inactif;
volatile ModeAffichage  modeAffichage                       = chaqueCycle;
volatile ModeOperation  modeOperation                       = demarrage;


void choisirConfiguration();


/**
*  Permet de changer le mode d'opération lorsque nous appuyons sur le bouton-poussoir sur D2.
*/
ISR(INT0_vect) 
{
    if (modeOperation == detection) 
        modeOperation = manoeuvre;
    EIFR |= (1 << INTF0);
}


/**
*  Permet de compter lorsque la minuterie 0 (sur 8 bits) effectue un Overflow.
*/
ISR(TIMER0_OVF_vect) 
{
    nCentiemes += N_SECONDES_PAR_OVERFLOWS;
    ++nOverflows;

    switch (frequenceLectureCapteurs) {
        case FREQUENCE_BOUTON_1:
            drapeau1 = drapeau2 = drapeau3 = drapeau4 = FREQUENCE_UNE_FOIS_SECONDE;
            break;

        case FREQUENCE_BOUTON_2:
            drapeau1 = drapeau2 = FREQUENCE_UNE_FOIS_SECONDE;
            drapeau3 = drapeau4 = FREQUENCE_DEUX_FOIS_SECONDE;
            break;

        case FREQUENCE_BOUTON_4:
            drapeau1 = FREQUENCE_UNE_FOIS_SECONDE;
            drapeau2 = FREQUENCE_PREMIER_QUART;
            drapeau3 = FREQUENCE_DEUX_FOIS_SECONDE;
            drapeau4 = FREQUENCE_DERNIER_QUART;
            break;
    }

    if (nOverflows == drapeau1 || nOverflows == drapeau2 || nOverflows == drapeau3 || nOverflows == drapeau4)
        if (modeOperation == detection)
            afficher = true;

    if (nOverflows == OVERFLOWS_DANS_UNE_SECONDE){
        ++nSecondes;
        nOverflows = 0;
        nCentiemes = 0;
    }

    if (nSecondes == SECONDES_DANS_UNE_MINUTE) {
        ++nMinutes;
        nSecondes = 0;
    }

    TIFR0 |= 1 << TOV0;
}


/**
*  Permet de changer le mode du clavier lorsqu'il est appuyé.
*/
ISR (PCINT2_vect) 
{
    using global::clavier;

    PCMSK2 = 0;

    /* 
        Utile pour que les connexions électriques du clavier aient le temps de se faire.
        On évite alors qu'une touche du clavier soit prise pour une autre.
    */
    _delay_ms(DELAI_CINQ_MS); 

    uint8_t rangeeActiveClavier     = NON_DEFINI;
    uint8_t colonneActiveClavier    = NON_DEFINI;
        
    if (PINC & (1 << PC4))
        colonneActiveClavier = COLONNE_1;

    else if (PINC & (1 << PC3))
        colonneActiveClavier = COLONNE_2;

    else if (PINC & (1 << PC2))
        colonneActiveClavier = COLONNE_3;

    clavier.configurerColonnesSorties(); 

    if (PINC & (1 << PC5))
        rangeeActiveClavier = RANGEE_1;

    else if (PINC & (1 << PC6))
        rangeeActiveClavier = RANGEE_2;

    else if (PINC & (1 << PC7))
        rangeeActiveClavier = RANGEE_3;
    
    clavier.determinerBouton(colonneActiveClavier, rangeeActiveClavier);
    
    choisirConfiguration();
    boutonPrecedent = clavier.getBouton();

    clavier.configurerRangeesSorties();

    PCIFR = (1 << PCIF2);
    PCMSK2 = ACTIVER_INTERRUPTION_COLONNE;
}


/**
*  Permet d'éteindre les deux couples de panneaux 7 segments.
*/
void Robot::fermerPanneaux7Segments()
{
    panneauxGauche.reinitialiserPanneauxPort();
    panneauxDroite.reinitialiserPanneauxPort();
}


/**
*  Permet de transformer l'affichage d'un nombre hexadécimal en nombre décimal sur 8 bits
*  (pour le clavier, bouton #).
*  \param	[const uint8_t]	 nombreHexadecimal	<Le nombre hexadécimal initial à modifier.>
*  \return	[uint8_t]				            <Le nombre décimal sur 8 bits modifié.>
*/
uint8_t transformerDecHex(const uint8_t nombreHexadecimal) 
{
    const uint8_t chiffreGauche   = nombreHexadecimal / FACTEUR_DECIMAL;
    const uint8_t chiffreDroit    = nombreHexadecimal - chiffreGauche * FACTEUR_DECIMAL;

    return chiffreDroit | (chiffreGauche << DEPLACER_VERS_PANNEAU_GAUCHE);
}


/**
*  Permet d'afficher la vitesse des moteurs sur les panneaux 7 segments.
*  \param	[const uint8_t]	 vitesseMoteurGauche	<La vitesse du moteur gauche à afficher.>
*  \param	[const uint8_t]	 vitesseMoteurDroite	<La vitesse du moteur droit à afficher.>
*/
void Robot::afficherVitessePanneaux7Segments(const uint8_t vitesseMoteurGauche, const uint8_t vitesseMoteurDroite) 
{
    if (estDecimal){
        panneauxGauche.afficherValeur(transformerDecHex(vitesseMoteurGauche));
        panneauxDroite.afficherValeur(transformerDecHex(vitesseMoteurDroite));
    }

    else {
        panneauxGauche.afficherValeur(vitesseMoteurGauche);
        panneauxDroite.afficherValeur(vitesseMoteurDroite);
    }
}


/**
*  Permet de régler la vitesse des moteurs.
*  \param	[const uint8_t]	 vitesseMoteurGauche    <La vitesse à régler pour le moteur gauche.>
*  \param	[const uint8_t]	 vitesseMoteurDroite    <La vitesse à régler pour le moteur droit.>
*/
void Robot::setVitesseMoteurs(int8_t vitesseMoteurGauche, int8_t vitesseMoteurDroite)
{
    const bool sensMoteurGauche = vitesseMoteurGauche >= VITESSE_NULLE;
    const bool sensMoteurDroite = vitesseMoteurDroite >= VITESSE_NULLE;

    vitesseMoteurGauche = sensMoteurGauche ? vitesseMoteurGauche : -vitesseMoteurGauche;
    vitesseMoteurDroite = sensMoteurDroite ? vitesseMoteurDroite : -vitesseMoteurDroite;

    controleurMoteurs.setVitesseMoteur2(vitesseMoteurGauche);
    controleurMoteurs.setSensMoteur2(sensMoteurGauche);
    controleurMoteurs.setVitesseMoteur1(vitesseMoteurDroite);
    controleurMoteurs.setSensMoteur1(sensMoteurDroite);

    if (modeOperation == manoeuvre)
        afficherVitessePanneaux7Segments(vitesseMoteurGauche, vitesseMoteurDroite);
}


/**
*  Permet de réaliser la manoeuvre 1.
*/
void Robot::manoeuvre1()
{
    int8_t vitesseMoteurGauche = -VITESSE_INITIALE_MANOEUVRE_1_ET_2;
    int8_t vitesseMoteurDroite = VITESSE_INITIALE_MANOEUVRE_1_ET_2;

    setVitesseMoteurs(vitesseMoteurGauche, vitesseMoteurDroite);
    _delay_ms(DELAI_UNE_SECONDE_ET_DEMIE_MS);

    vitesseMoteurGauche = VITESSE_INITIALE_MANOEUVRE_1_ET_2;

    setVitesseMoteurs(vitesseMoteurGauche, vitesseMoteurDroite);
    _delay_ms(DELAI_DEUX_SECONDES_MS);

    vitesseMoteurDroite = -VITESSE_INITIALE_MANOEUVRE_1_ET_2;

    setVitesseMoteurs(vitesseMoteurGauche, vitesseMoteurDroite);
    _delay_ms(DELAI_UNE_SECONDE_ET_DEMIE_MS);

    for (uint8_t i = 0; i <= N_ITERATIONS_MANOEUVRE_1_ET_2; ++i) {
        vitesseMoteurGauche = VITESSE_INITIALE_MANOEUVRE_1_ET_2 + i * BOND_MANOEUVRE_1_ET_2;
        vitesseMoteurDroite = VITESSE_INITIALE_MANOEUVRE_1_ET_2 + i * BOND_MANOEUVRE_1_ET_2;
        setVitesseMoteurs(vitesseMoteurGauche, VITESSE_INITIALE_MANOEUVRE_1_ET_2 + i * BOND_MANOEUVRE_1_ET_2);
        _delay_ms(DELAI_ENTRE_BONDS_MANOEUVRE_1_ET_2);
    }

    _delay_ms(DELAI_DEUX_SECONDES_MS);
}


/**
*  Permet de réaliser la manoeuvre 2.
*/
void Robot::manoeuvre2()
{
    int8_t vitesseMoteurGauche = VITESSE_INITIALE_MANOEUVRE_1_ET_2;
    int8_t vitesseMoteurDroite = -VITESSE_INITIALE_MANOEUVRE_1_ET_2;

    setVitesseMoteurs(vitesseMoteurGauche, vitesseMoteurDroite);
    _delay_ms(DELAI_UNE_SECONDE_ET_DEMIE_MS);

    vitesseMoteurDroite = VITESSE_INITIALE_MANOEUVRE_1_ET_2;

    setVitesseMoteurs(vitesseMoteurGauche, vitesseMoteurDroite);
    _delay_ms(DELAI_DEUX_SECONDES_MS);

    vitesseMoteurGauche = -VITESSE_INITIALE_MANOEUVRE_1_ET_2;

    setVitesseMoteurs(vitesseMoteurGauche, vitesseMoteurDroite);
    _delay_ms(DELAI_UNE_SECONDE_ET_DEMIE_MS);

    for (uint8_t i = 0; i <= N_ITERATIONS_MANOEUVRE_1_ET_2; ++i) {
        vitesseMoteurGauche = VITESSE_INITIALE_MANOEUVRE_1_ET_2 + i * BOND_MANOEUVRE_1_ET_2;
        vitesseMoteurDroite = VITESSE_INITIALE_MANOEUVRE_1_ET_2 + i * BOND_MANOEUVRE_1_ET_2;
        setVitesseMoteurs(vitesseMoteurGauche, vitesseMoteurDroite);
        _delay_ms(DELAI_ENTRE_BONDS_MANOEUVRE_1_ET_2);
    }

    _delay_ms(DELAI_DEUX_SECONDES_MS);
}


/**
*  Permet de réaliser la manoeuvre 3.
*/
void Robot::manoeuvre3()
{
    int8_t vitesseMoteurGauche = -VITESSE_INITIALE_MANOEUVRE_3;
    int8_t vitesseMoteurDroite = -VITESSE_INITIALE_MANOEUVRE_3;

    setVitesseMoteurs(vitesseMoteurGauche, vitesseMoteurDroite);
    _delay_ms(DELAI_UNE_SECONDE_MS);

    vitesseMoteurGauche = -NOUVELLE_VITESSE_MANOEUVRE_3;
    vitesseMoteurDroite = NOUVELLE_VITESSE_MANOEUVRE_3;

    setVitesseMoteurs(vitesseMoteurGauche, vitesseMoteurDroite);
    _delay_ms(DELAI_UNE_SECONDE_ET_DEMIE_MS);

    for (uint8_t i = 0; i <= N_ITERATIONS_MANOEUVRE_3_BOUCLE_1; ++i) {
        vitesseMoteurGauche = BOND_MANOEUVRE_3_BOUCLE_PREMIERE * i;
        vitesseMoteurDroite = BOND_MANOEUVRE_3_BOUCLE_PREMIERE * i;
        setVitesseMoteurs(vitesseMoteurGauche, vitesseMoteurDroite);
        _delay_ms(DELAI_ENTRE_BONDS_MANOEUVRE_3);
    }

    for (uint8_t i = 0; i <= N_ITERATIONS_MANOEUVRE_3_BOUCLE_2; ++i) {
        vitesseMoteurGauche = VITESSE_MAXIMALE_MANOEUVRE_3 - BOND_MANOEUVRE_3_BOUCLE_SECONDE * i;
        vitesseMoteurDroite = VITESSE_MAXIMALE_MANOEUVRE_3 - BOND_MANOEUVRE_3_BOUCLE_SECONDE * i;
        setVitesseMoteurs(vitesseMoteurGauche, vitesseMoteurDroite);
        _delay_ms(DELAI_UNE_DEMIE_SECONDE_MS);
    }

    _delay_ms(DELAI_DEUX_SECONDES_MS);
}


/**
*  Permet de réaliser la manoeuvre 4.
*/
void Robot::manoeuvre4()
{
    int8_t vitesseMoteurGauche = VITESSE_INITIALE_MANOEUVRE_4_ET_5;
    int8_t vitesseMoteurDroite = VITESSE_INITIALE_MANOEUVRE_4_ET_5;
    
    for (uint8_t i = 0; i <= N_ITERATIONS_MANOEUVRE_4_ET_5; ++i) {
        vitesseMoteurGauche = VITESSE_INITIALE_MANOEUVRE_4_ET_5 - i * BOND_MANOEUVRE_4_ET_5;
        setVitesseMoteurs(vitesseMoteurGauche, vitesseMoteurDroite);
        _delay_ms(DELAI_UN_QUART_SECONDE_MS);
    }

    _delay_ms(DELAI_UNE_SECONDE_ET_DEMIE_MS);

    for (uint8_t i = 0; i <= N_ITERATIONS_MANOEUVRE_4_ET_5; ++i) {
        vitesseMoteurGauche = NOUVELLE_VITESSE_MANOEUVRE_4_ET_5 + i * BOND_MANOEUVRE_4_ET_5;
        setVitesseMoteurs(vitesseMoteurGauche, vitesseMoteurDroite);
        _delay_ms(DELAI_UN_QUART_SECONDE_MS);
    }

    _delay_ms(DELAI_DEUX_SECONDES_MS);
}


/**
*  Permet de réaliser la manoeuvre 5.
*/
void Robot::manoeuvre5()
{
    int8_t vitesseMoteurGauche = VITESSE_INITIALE_MANOEUVRE_4_ET_5;
    int8_t vitesseMoteurDroite = VITESSE_INITIALE_MANOEUVRE_4_ET_5;

    for (uint8_t i = 0; i <= N_ITERATIONS_MANOEUVRE_4_ET_5; ++i) {
        vitesseMoteurDroite = VITESSE_INITIALE_MANOEUVRE_4_ET_5 - i * BOND_MANOEUVRE_4_ET_5;
        setVitesseMoteurs(vitesseMoteurGauche, vitesseMoteurDroite);
        _delay_ms(DELAI_UN_QUART_SECONDE_MS);
    }

    _delay_ms(DELAI_UNE_SECONDE_ET_DEMIE_MS);

    for (uint8_t i = 0; i <= N_ITERATIONS_MANOEUVRE_4_ET_5; ++i) {
        vitesseMoteurDroite = NOUVELLE_VITESSE_MANOEUVRE_4_ET_5 + i * BOND_MANOEUVRE_4_ET_5;
        setVitesseMoteurs(vitesseMoteurGauche, vitesseMoteurDroite);
        _delay_ms(DELAI_UN_QUART_SECONDE_MS);
    }

    _delay_ms(DELAI_DEUX_SECONDES_MS);
}


/**
*  Permet de choisir la configuration du clavier et de l'imprimer à l'écran.
*/
void choisirConfiguration() 
{
    using global::clavier;
    using global::transmetteur;

    switch (clavier.getBouton()) {
        case (inactif):
            break;

        case(bouton1):
            transmetteur.envoyerMessage(" > Bouton 1 !\n");
            if (frequenceLectureCapteurs != FREQUENCE_BOUTON_1) {
                transmetteur.envoyerMessage(" > Mode 1 - Frequence d'affichage = 1 fois/seconde\n");
                frequenceLectureCapteurs = FREQUENCE_BOUTON_1;
            }
            break;

        case(bouton2):
            transmetteur.envoyerMessage(" > Bouton 2 !!\n");
            if (frequenceLectureCapteurs != FREQUENCE_BOUTON_2) {
                transmetteur.envoyerMessage(" > Mode 2 - Frequence d'affichage = 2 fois/seconde\n");
                frequenceLectureCapteurs = FREQUENCE_BOUTON_2;
            }
            break;

        case(bouton4):
            transmetteur.envoyerMessage(" > Bouton 4 !!!\n");
            if (frequenceLectureCapteurs != FREQUENCE_BOUTON_4) {
                transmetteur.envoyerMessage(" > Mode 4 - Frequence d'affichage = 4 fois/seconde\n");
                frequenceLectureCapteurs = FREQUENCE_BOUTON_4;
            }
            break;

        case(boutonR):
            transmetteur.envoyerMessage(" > Bouton R !\n");
            if (modeAffichage != chaqueCycle) {
                transmetteur.envoyerMessage(" > Mode R - Affichage a chaque cycle de lecture des capteurs. \n");
                modeAffichage = chaqueCycle;
            }
            break;

        case(boutonV):
            transmetteur.envoyerMessage(" > Bouton V !!\n");
            if (modeAffichage != changementValeur) {
                transmetteur.envoyerMessage(" > Mode V - Affichage a chaque changement de valeurs. \n");
                modeAffichage = changementValeur;
            }
            break;

        case(boutonC):
            transmetteur.envoyerMessage(" > Bouton C !!!\n");
            if (modeAffichage != changementCategorie) {
                transmetteur.envoyerMessage(" > Mode C - Affichage a chaque changement de categories. \n");
                modeAffichage = changementCategorie;
            }
            break;

        case(boutonI):
            transmetteur.envoyerMessage(" > Bouton I !\n");
            if (estLectureDesCapteursInterne != true) {
                transmetteur.envoyerMessage(" > Mode I - Utilisation du CAN interne\n");
                estLectureDesCapteursInterne = true;
            }
            break;

        case(boutonE):
            transmetteur.envoyerMessage(" > Bouton E !!\n");
            if (estLectureDesCapteursInterne != false) {
                transmetteur.envoyerMessage(" > Mode E - Utilisation du CAN externe\n");
                estLectureDesCapteursInterne = false;  
            }  
            break;

        case(boutonDiese):
            transmetteur.envoyerMessage(" > Bouton # !!!\n");

            if (estDecimal) {
                transmetteur.envoyerMessage(" > Mode # - Affichage 7 segments en hexadecimal\n");
                estDecimal = false;
            }

            else {
                transmetteur.envoyerMessage(" > Mode # - Affichage 7 segments en decimal\n");
                estDecimal = true;
            }

            break;
    }
}


/**
*  Permet de partir la minuterie 0 pour compter le temps. Veuillez vous référer à l'en-tête afin
*  de savoir quels pins/ports sont utilisés.
*/
void partirMinuterie() 
{
    cli();

    TCCR0B  |= (1 << CS02);
    TCNT0    = 0;
    TIMSK0  |= (1 << TOIE0);
    TIFR0   |= (1 << TOV0);

    sei();
}


/**
*  Permet de tronquer une distance pour ne prendre que les décimales entières.
*  \param	[const float]	 distance	<La distance que l'on souhaite tronquer.>
*  \return	[uint8_t]				    <Les décimales entières de la distance en paramètre.>
*/
uint8_t tronquerDecimales(const float distance)
{
    return uint8_t((distance - int(distance)) * FACTEUR_TRONCATURE);
}


/**
*  Permet d'interpréter quelle manoeuvre en particulier est exécutée.
*  \param	[const ModeManoeuvre&]	 modeManoeuvre	<Le mode de manoeuvre que l'on souhaite interpréter.>
*  \return	[char]				                    <La manoeuvre sous forme de caractère ('-' si aucune).>
*/
char interpreterManoeuvre(const ModeManoeuvre& modeManoeuvre)
{
    uint8_t numManoeuvre = modeManoeuvre;

    if (numManoeuvre == 0)
        return '-';

    else
        return char(numManoeuvre + DEBUT_CHIFFRE_TABLE_ASCII);
}


/**
*  Permet d'interpréter la catégorie qui découle de la manoeuvre.
*  \param	[const CategorieDistance&]	 categorieDistance	<La catégorie que l'on souhaite interpréter.>
*  \return	[static const char*]				            <Un pointeur vers un tableau statique qui
*                                                            représente la catégorie de distance interprétée.>
*/
static const char* interpreterCategorie(const CategorieDistance& categorieDistance)
{
    switch (categorieDistance) {
        case ok:
            return CATEGORIE_OK;

        case attention:
            return CATEGORIE_ATTENTION;

        case danger:
            return CATEGORIE_DANGER;
    }

    return nullptr; // Ne rien retourner si la catégorie de distance n'a pas été proprement initialisée
}


/**
*  Permet d'afficher les données de détection (temps, distances et catégorie) lors du mode détection.
*  \param	[const LectureTroisCapteurs&]   troisCapteurs	<Les trois capteurs contenant les lectures
*                                                            respectives des distances.>
*  \param	[const ModeManoeuvre&]          modeManoeuvre	<La manoeuvre à laquelle nous nous trouvons.
*/
void Robot::affichageDetection(const LectureTroisCapteurs& troisCapteurs, const ModeManoeuvre& modeManoeuvre) 
{
    using global::transmetteur;

    char tamponMessage[TAILLE_TAMPON_DETECTION];

    sprintf(tamponMessage, TEXTE_DETECTION,
        nMinutes, nSecondes, int(nCentiemes * CENTIEMES_SECONDE_DANS_UNE_SECONDE),
        uint8_t(troisCapteurs.lectureCapteurGauche.distance), tronquerDecimales(troisCapteurs.lectureCapteurGauche.distance),
        uint8_t(troisCapteurs.lectureCapteurCentre.distance), tronquerDecimales(troisCapteurs.lectureCapteurCentre.distance),
        uint8_t(troisCapteurs.lectureCapteurDroite.distance), tronquerDecimales(troisCapteurs.lectureCapteurDroite.distance),
        interpreterCategorie(troisCapteurs.lectureCapteurGauche.categorie),
        interpreterCategorie(troisCapteurs.lectureCapteurCentre.categorie),
        interpreterCategorie(troisCapteurs.lectureCapteurDroite.categorie),
        interpreterManoeuvre(modeManoeuvre)
    );

    transmetteur.envoyerMessage(tamponMessage);
}


/**
*  Permet d'enregistrer la lecture des trois capteurs.
*  \param	[LecteurCapteur&]   lecteur     <Le lecteur qui se charge de lire les distances des capteurs.>
*  \return	[LectureTroisCapteurs]			<La lecture des trois capteurs.>
*/
LectureTroisCapteurs lireCapteurs(LecteurCapteur& lecteur)
{
    LectureTroisCapteurs lectures;

    lectures.lectureCapteurGauche = lecteur.lireCapteur(CAPTEUR_GAUCHE, estLectureDesCapteursInterne);
    _delay_ms(DELAI_CINQ_MS);
    lectures.lectureCapteurCentre = lecteur.lireCapteur(CAPTEUR_CENTRE, estLectureDesCapteursInterne);
    _delay_ms(DELAI_CINQ_MS);
    lectures.lectureCapteurDroite = lecteur.lireCapteur(CAPTEUR_DROIT, estLectureDesCapteursInterne);

    return lectures;
}


/**
*  Permet d'initialiser le bouton-poussoir par interruption.
*/
void initialisationBoutonPoussoir() 
{
    cli();

    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC01);

    sei();
}


/**
*  Permet de déterminer la suite du programme en mode manoeuvre selon la lecture des distances 
*  des trois capteurs.
*  \param	[const LectureTroisCapteurs&]   lectures    <Les lectures des distances des trois capteurs.>
*  \return	[ModeManoeuvre]			                    <La manoeuvre à exécuter.>
*/
ModeManoeuvre determinerManoeuvre(const LectureTroisCapteurs& lectures)
{
    if (lectures.lectureCapteurGauche.categorie == ok && 
        lectures.lectureCapteurCentre.categorie == attention && 
        lectures.lectureCapteurDroite.categorie == attention)
        return manoeuvreUn;

    else if (lectures.lectureCapteurGauche.categorie == attention && 
             lectures.lectureCapteurCentre.categorie == attention && 
             lectures.lectureCapteurDroite.categorie == ok)
        return manoeuvreDeux;

    else if (lectures.lectureCapteurGauche.categorie == danger && 
             lectures.lectureCapteurCentre.categorie == danger &&
             lectures.lectureCapteurDroite.categorie == danger)
        return manoeuvreTrois;
    
    else if (lectures.lectureCapteurGauche.categorie == ok && 
             lectures.lectureCapteurCentre.categorie == ok && 
             lectures.lectureCapteurDroite.categorie == danger)
        return manoeuvreQuatre;
    
    else if (lectures.lectureCapteurGauche.categorie == danger &&
             lectures.lectureCapteurCentre.categorie == ok && 
             lectures.lectureCapteurDroite.categorie == ok)
        return manoeuvreCinq;
    
    else
        return aucune;
}


/**
*  Exécute la manoeuvre précise, déterminée plus tôt au cours du mode de détection.
*  \param	[const ModeManoeuvre&]   manoeuvreAEffectuer    <La manoeuvre à effectuer.>
*/
void Robot::faireManoeuvre(const ModeManoeuvre& manoeuvreAEffectuer)
{
    using global::transmetteur;

    switch (manoeuvreAEffectuer) {
        case manoeuvreUn:
        {
            transmetteur.envoyerMessage(" > Manoeuvre 1 \n");
            manoeuvre1();
            break;
        }

        case manoeuvreDeux:
        {
            transmetteur.envoyerMessage(" > Manoeuvre 2 \n");
            manoeuvre2();
            break;
        }

        case manoeuvreTrois:
        {
            transmetteur.envoyerMessage(" > Manoeuvre 3 \n");
            manoeuvre3();
            break;
        }

        case manoeuvreQuatre:
        {
            transmetteur.envoyerMessage(" > Manoeuvre 4 \n");
            manoeuvre4();
            break;
        }

        case manoeuvreCinq:
        {
            transmetteur.envoyerMessage(" > Manoeuvre 5 \n");
            manoeuvre5();
            break;
        }

        case aucune:
        {
            transmetteur.envoyerMessage("\nCombinaison non evaluee.\n");
            _delay_ms(DELAI_DEUX_SECONDES_MS);
        }

    }

    // Réinitialisation des panneaux 7 segments et des moteurs suite à la manoeuvre effectuée
    setVitesseMoteurs(0, 0);
    fermerPanneaux7Segments();
}


/**
*  Débute l'exécution du robot en mode démarrage.
*/
void Robot::executer()
{
    using global::clavier;
    using global::transmetteur;

    initialisationBoutonPoussoir();
    
    while (true) {
        switch (modeOperation) {
            case demarrage: {
                char tamponMessageBps[TAILLE_TAMPON];

                sprintf(tamponMessageBps, TEXTE_BPS, VITESSE_TRANSMISSION_BAUDS);
                transmetteur.envoyerMessage(tamponMessageBps);

                panneauxGauche.afficherValeur(VALEUR_INITIALE_PANNEAU_GAUCHE);
                panneauxDroite.afficherValeur(VALEUR_INITIALE_PANNEAU_DROITE);

                setVitesseMoteurs(MOTEUR_VITESSE_MAXIMALE, MOTEUR_VITESSE_MAXIMALE);
                _delay_ms(DELAI_UNE_SECONDE_MS);
                setVitesseMoteurs(-MOTEUR_VITESSE_MAXIMALE, -MOTEUR_VITESSE_MAXIMALE);
                _delay_ms(DELAI_UNE_SECONDE_MS);
                setVitesseMoteurs(VITESSE_NULLE, VITESSE_NULLE);
                fermerPanneaux7Segments();

                transmetteur.envoyerMessage(" > Appuyer sur une touche du clavier pour choisir la configuration \n");
                modeOperation = detection;
                break;
            }

            case detection: {
                    const LectureTroisCapteurs lectures = lireCapteurs(lecteur);
                    manoeuvreAEffectuer = determinerManoeuvre(lectures);

                        switch (modeAffichage) {
                            case chaqueCycle:
                                if (afficher) {
                                    afficher = false;
                                    affichageDetection(lectures, manoeuvreAEffectuer);
                                }
                                break;

                            case changementValeur:
                                if (ancienneLectures.lectureCapteurGauche.distance != lectures.lectureCapteurGauche.distance || 
                                    ancienneLectures.lectureCapteurCentre.distance != lectures.lectureCapteurCentre.distance || 
                                    ancienneLectures.lectureCapteurDroite.distance != lectures.lectureCapteurDroite.distance)
                                        affichageDetection(lectures, manoeuvreAEffectuer);
                                break;

                            case changementCategorie:
                                if (ancienneLectures.lectureCapteurGauche.categorie != lectures.lectureCapteurGauche.categorie || 
                                    ancienneLectures.lectureCapteurCentre.categorie != lectures.lectureCapteurCentre.categorie ||
                                    ancienneLectures.lectureCapteurDroite.categorie != lectures.lectureCapteurDroite.categorie)
                                        affichageDetection(lectures, manoeuvreAEffectuer);
                                break;
                        }

                    ancienneLectures = lectures;
                    break;
            }

            case manoeuvre: {
                faireManoeuvre(manoeuvreAEffectuer);
                modeOperation = detection;
                break;
            }
        }
    }
}


/**
*  Réglages des ports et début délégation de l'exécution du programme.
*/
int main()
{
    Robot robot{};
    partirMinuterie();

    DDRA = DDR_PORTA;
    DDRB = DDR_PORTB;
    DDRD = DDR_PORTD;

    robot.executer();
}
