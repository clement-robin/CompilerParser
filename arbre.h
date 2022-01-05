/* Auteurs : Clement ROBIN & Lucas DESHAYES */

#ifndef ARBRE
#define ARBRE

#include "sources/read_file.h"
#include "sources/LRGrammar.h"


typedef struct arbre
{
    struct arbre* fils[100];
    char valeur;
    int nombreFils;
}arbre;


void affichage_arbre(arbre * racine);
void free_arbre(arbre * racine);


#endif