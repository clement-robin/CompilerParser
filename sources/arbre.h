/* Auteurs : Clement ROBIN & Lucas DESHAYES */

#ifndef ARBRE
#define ARBRE

#include "read_file.h"
#include "LRGrammar.h"

#define TAILLEMAX 256

typedef struct arbre
{
    struct arbre* fils[TAILLEMAX];
    char valeur;
    int nombreFils;
}arbre;


void affichage_arbre(arbre * racine);
void free_arbre(arbre * racine);


#endif