/* Auteur : Clement ROBIN & Lucas DESHAYES */

#ifndef OUTILS
#define OUTILS

#include "sources/read_file.h"
#include "sources/LRGrammar.h"

#define bool unsigned int
#define true 1
#define false 0

/******* Fonctions de tests des arguments ******/

void verification_nombre_arguments(int argc, char const *argv[]);
bool verification_fichier(const char * fichier, file_read analyseurLR);



/******* Fonctions d'affichage ******/

void affichage_debut(int tailleMot);
void affichage_ligne(char * val, char * flot, char * pile,int tailleMot);





#endif