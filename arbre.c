/* Auteur : Clement ROBIN & Lucas DESHAYES */

#include "arbre.h"

/******* FONCTIONS ******/

/**
 *  
 * 
 * @param racine 
 */
void affichage_arbre(arbre *racine){
    printf("%c(",racine->valeur);
    for (int i = 0; i < racine->nombreFils; i++)
    {
        affichage_arbre(racine->fils[i]);
    }
    printf(")");
};

/**
 * 
 * 
 * @param racine 
 */
void free_arbre(arbre * racine){
    if (racine != NULL) {
        for (int i = 0; i < racine->nombreFils; i++)
        {
            free_arbre(racine->fils[i]);
        }
        free(racine);
    }
};



 
