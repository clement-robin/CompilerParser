/* Auteurs : Clement ROBIN & Lucas DESHAYES */

#include "arbre.h"

/******* FONCTIONS ******/



/**
 * La fonction affichage_arbre permet d'afficher l'arbre de manière lineaire
 * Exemple S(a()S()b())
 * @param racine pointeur vers la racince de l'arbre que l'on veut souhaite afficher)
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
 * La
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



 
