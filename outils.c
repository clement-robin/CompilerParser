/* Author : Clement ROBIN & Lucas DESHAYES */

#include "outils.h"


/******* FONCTIONS ******/

/**
 * La fonction affiche_debut affiche la mise en page de l'analyseur SLR
 * @param tailleMot taille du mot a analyser
 */
void affichage_debut(int tailleMot) {
    printf("\n\n   ");
    for (int i = 0; i < tailleMot-2; i++)
    {
        printf(" ");
    }
    printf("Flot  |   Pile\n  ------------------------------\n");
}

/**
 * La fonction affiche_ligne permet d'afficher une ligne de notre analyseur SLR
 * @param val val est la regle appliquer sur la ligne
 * @param flot flot a afficher
 * @param pile pile a afficher
 * @param tailleMot taille du mot 
 */
void affichage_ligne(char * val, char * flot, char * pile,int tailleMot) {
    if (strcmp(pile,"acc") == 0 || strcmp(pile,"err") == 0)
        printf("  ");
    else
        printf("%s",val);
    int diff = tailleMot-strlen(flot);
    for (int i = 0; i < 4+diff; i++)
    {
        printf(" ");
    }
    if (strcmp(pile,"acc") == 0)
        printf("accept");
    else if (strcmp(pile,"err") == 0)
        printf("error");
    else
        printf("%s | %s\n",flot,pile);

}
