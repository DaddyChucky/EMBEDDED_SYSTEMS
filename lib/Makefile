##
#	Auteur: Genevieve Pelletier-McDuff, Charles De Lafontaine, Matis Gregoire, Fanilotiana Guy et Ismail Essid
# 
#	Description: Permet de compiler un ou plusieurs fichiers .c/.cpp en .o et .d pour former une librairie statique.
#
##

# Nom du projet
PROJECTNAME=libprojet

# Fichiers sources
PRJSRC=boutonPoussoir.cpp can.cpp controleDEL.cpp controleMinuterie.cpp \
	   controleMoteurs.cpp EEPROMLectureEtEcriture.cpp RS232.cpp debug.cpp \
	   affichage7Segments.cpp LecteurCapteur.cpp Clavier.cpp

# Variables additionnelles pour créer l'archive
# Pour créer l'archive (c), insérer les fichiers membres dans l'archive (r)
# et écrire/modifier l'index d'un fichier objet dans l'archive (s)
# pour plus d'informations: https://linux.die.net/man/1/avr-ar
AR_VARS=crs

include ../lib/Makefile_commun/Makefile_lib