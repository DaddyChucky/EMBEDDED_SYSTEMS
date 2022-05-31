#define DDR_PORTA 0xFD
#define DDR_PORTB 0xFD
#define DDR_PORTD 0xF8

enum ModeOperation { demarrage, detection, manoeuvre };
enum ModeManoeuvre { aucune, manoeuvreUn, manoeuvreDeux, manoeuvreTrois, manoeuvreQuatre, manoeuvreCinq };
enum ModeAffichage { chaqueCycle, changementValeur, changementCategorie };

constexpr uint16_t      VALEUR_INITIALE_PANNEAU_GAUCHE      = 0xAB;
constexpr uint16_t      VALEUR_INITIALE_PANNEAU_DROITE      = 0xCD;
constexpr uint8_t       DELAI_CINQ_MS                       = 5;
constexpr uint16_t      DELAI_UN_QUART_SECONDE_MS           = 250;
constexpr uint16_t      DELAI_UNE_DEMIE_SECONDE_MS          = 500;
constexpr uint16_t      DELAI_UNE_SECONDE_MS                = 1000;
constexpr uint16_t      DELAI_UNE_SECONDE_ET_DEMIE_MS       = 1500;
constexpr uint16_t      DELAI_DEUX_SECONDES_MS              = 2000;
constexpr uint16_t      VITESSE_TRANSMISSION_BAUDS          = 9600;
constexpr uint8_t       N_ITERATIONS_MANOEUVRE_1_ET_2       = 12;
constexpr uint8_t       N_ITERATIONS_MANOEUVRE_3_BOUCLE_1   = 33;
constexpr uint8_t       N_ITERATIONS_MANOEUVRE_3_BOUCLE_2   = 5;
constexpr uint8_t       N_ITERATIONS_MANOEUVRE_4_ET_5       = 15;
constexpr uint8_t       VITESSE_INITIALE_MANOEUVRE_1_ET_2   = 35;
constexpr uint8_t       VITESSE_INITIALE_MANOEUVRE_3        = 50;
constexpr uint8_t       VITESSE_INITIALE_MANOEUVRE_4_ET_5   = 78;
constexpr uint8_t       NOUVELLE_VITESSE_MANOEUVRE_3        = 70;
constexpr uint8_t       NOUVELLE_VITESSE_MANOEUVRE_4_ET_5   = 48;
constexpr uint8_t       VITESSE_MAXIMALE_MANOEUVRE_3        = 99;
constexpr uint8_t       DELAI_ENTRE_BONDS_MANOEUVRE_1_ET_2  = 125;
constexpr uint8_t       DELAI_ENTRE_BONDS_MANOEUVRE_3       = 50;
constexpr uint8_t       BOND_MANOEUVRE_1_ET_2               = 5;
constexpr uint8_t       BOND_MANOEUVRE_3_BOUCLE_PREMIERE    = 3;
constexpr uint8_t       BOND_MANOEUVRE_3_BOUCLE_SECONDE     = 5;
constexpr uint8_t       BOND_MANOEUVRE_4_ET_5               = 2;
constexpr uint8_t       VITESSE_NULLE                       = 0;
constexpr uint8_t       FREQUENCE_UNE_FOIS_SECONDE          = 1;
constexpr uint8_t       DEPLACER_VERS_PANNEAU_GAUCHE        = 4;
constexpr uint8_t       FREQUENCE_PREMIER_QUART             = 31;
constexpr uint8_t       FREQUENCE_DEUX_FOIS_SECONDE         = 61;
constexpr uint8_t       FREQUENCE_DERNIER_QUART             = 92;
constexpr uint8_t       FACTEUR_DECIMAL                     = 10;
constexpr uint8_t       FACTEUR_TRONCATURE                  = 10;
constexpr uint8_t       TAILLE_TAMPON                       = 10;
constexpr uint8_t       MOTEUR_VITESSE_MAXIMALE             = 100;
constexpr uint8_t       SECONDES_DANS_UNE_MINUTE            = 60;
constexpr uint8_t       OVERFLOWS_DANS_UNE_SECONDE          = 122;
constexpr uint8_t       FREQUENCE_BOUTON_1                  = 1;
constexpr uint8_t       FREQUENCE_BOUTON_2                  = 2;
constexpr uint8_t       FREQUENCE_BOUTON_4                  = 4;
constexpr uint8_t       DEBUT_CHIFFRE_TABLE_ASCII           = 48;
constexpr uint8_t       CAPTEUR_GAUCHE                      = 0;
constexpr uint8_t       CAPTEUR_CENTRE                      = 1;
constexpr uint8_t       CAPTEUR_DROIT                       = 2;
constexpr uint8_t       CENTIEMES_SECONDE_DANS_UNE_SECONDE  = 100;
constexpr uint8_t       TAILLE_TAMPON_DETECTION             = 150;
constexpr char          TEXTE_BPS[]                         = "%d bps\n";
constexpr char          TEXTE_DETECTION[]                   = "%02d:%02d.%02d - G:%02d.%01d C:%02d.%01d D:%02d.%01d - %s | %s | %s (%c)\n";
constexpr float         N_SECONDES_PAR_OVERFLOWS            = 0.008192f;

static constexpr char   CATEGORIE_OK[]                      = "OK";
static constexpr char   CATEGORIE_ATTENTION[]               = "ATTENTION";
static constexpr char   CATEGORIE_DANGER[]                  = "DANGER";
