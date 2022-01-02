/* Auteur : Clement ROBIN & Lucas DESHAYES */

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


arbre **neoudsRencontresOrphelins;
int tailleNeoudsRencontresOrphelins;

void print_arbre(arbre * racine);
void free_arbre(arbre * racine);
char recup_node(char caractereLu, char transition, grammar parGrammar);
void construire_arbre(char nodeRecup, signed char transition, grammar parGrammar);


#endif