/* Auteur : Clement ROBIN & Lucas DESHAYES */

#include "outils.h"

/******* FONCTIONS ******/

/**
 * La fonction affiche_debut affiche la mise en page de l'analyseur SLR
 * @param tailleMot taille du mot a analyser
 */
void affichage_debut(int tailleMot)
{
    printf("\n\n   ");
    for (int i = 0; i < tailleMot - 2; i++)
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
void affichage_ligne(char *val, char *flot, char *pile, int tailleMot)
{
    int espace = 0;
    int valeur = val[1] - '0';
    if (strcmp(pile, "acc") == 0 || strcmp(pile, "err") == 0)
        printf("  ");
    else
    {
        if (valeur >= 10)
        {
            val[1] = valeur / 10 + '0';
            val[2] = valeur % 10 + '0';
            espace = 1;
        }
        printf("%s", val);
        val[2] = '\0';
    }
    int diff = tailleMot - strlen(flot);
    for (int i = 0; i < 4 + diff - espace; i++)
    {
        printf(" ");
    }
    if (strcmp(pile, "acc") == 0)
        printf("accept");
    else if (strcmp(pile, "err") == 0)
        printf("error");
    else
    {
        int compteur = 0;
        while (pile[compteur] != '\0')
        {
            compteur++;
        }
        valeur = pile[compteur-1] -'0';
        if (valeur >= 10)
        {
           
            char *buffer = (char *)malloc((compteur + 3) * sizeof(char));
            strcpy(buffer, pile);

            buffer[compteur-1] = valeur / 10 + '0';
            buffer[compteur] = valeur % 10 + '0';
            buffer[compteur + 1] = '\0';
            printf("%s | %s\n", flot, buffer);
        }
        else
        {
            printf("%s | %s\n", flot, pile);
        }
    }
}

/**
 * La fonction ajoutDebutDeChaine permet d'ajouter au debut de la chaine une chaine 
 * tel que si la chaine etait S()b() et qu'on lui donne le caractere a
 * la fonction retourne a()S()b()
 * 
 * @param chaine chaine de caractere que l'on souahite modifier
 * @param caractere caratere que l'on souhaite ajouter
 * @return char * chaine que l'on retourne
 */
char * ajoutDebutDeChaine(char * chaine, char caractere) {
    char * ajoutDebut = (char *) malloc(100 * sizeof(char));

    sprintf(ajoutDebut,"%c()%s",caractere,chaine);

    return ajoutDebut;
}

/**
 * La fonction ajoutFinDeChaine permet d'ajouter a la fin de la chaine une chaine 
 * tel que si la chaine etait a()S() et qu'on lui donne le caractere b
 * la fonction retourne a()S()b()
 * 
 * @param chaine chaine de caractere que l'on souahite modifier
 * @param caractere caratere que l'on souhaite ajouter
 * @return char * chaine que l'on retourne
 */
char * ajoutFinDeChaine(char * chaine, char caractere) {
    sprintf(chaine,"%s%c()",chaine,caractere);

    return chaine;
}

/**
 * La fonction encadrerChaine permet d'encadrer une chaine 
 * tel que si la chaine etait a()S()b() et qu'on lui donne le caractere b
 * la fonction retourne S(a()S()b())
 * 
 * @param chaine chaine de caractere que l'on souahite modifier
 * @param caractere caratere que l'on souhaite ajouter
 * @return char * chaine que l'on retourne
 */
char * encadrerChaine(char * chaine, char caractere){
    char * ajoutDebut = (char *) malloc(100 * sizeof(char));

    sprintf(ajoutDebut,"%c(%s)",caractere,chaine);
    
    return ajoutDebut;
}