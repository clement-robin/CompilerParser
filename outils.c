/* Auteurs : Clement ROBIN & Lucas DESHAYES */

#include "outils.h"




/******* FONCTIONS ******/


    /*** VERIFICATION : bon nombre d'arguments ? -> 3 attendus ***/

void verification_nombre_arguments(int argc, char const *argv[])
{
    if (argc < 3)
    {
        printf("--> erreur -- trop peu d'arguments (tableau SLR et mot a tester requis)\n");
        exit(EXIT_FAILURE);
    }
    else if (argc > 3)
    {
        printf("--> erreur -- trop d'arguments (tableau SLR et mot a tester requis)\n");
        for (int i = 3; i < argc; i++)
        {
            printf("          %s <-- argument en trop\n", argv[i]);
        }
        exit(EXIT_FAILURE);
    }   
}

    /*** VERIFICATION : le fichier existe ? (dans assets/) ***/

bool verification_fichier(const char * fichier, file_read analyseurLR) {

    char * pathFichier = (char *)malloc(strlen(fichier) + 1 * sizeof(char));
    strcpy(pathFichier, fichier);

    FILE *file = fopen(pathFichier, "r+");

    if (file != NULL)
    {
        printf("--> Le fichier %s existe\n", pathFichier);

        /*** VERIFICATION : le fichier est lisible par read_file ? ***/
        analyseurLR = read_file(pathFichier);
        printf("--> Le fichier %s est bien lu\n", pathFichier);
        fclose(file);
    }
    else
    {
        fprintf(stderr, "--> erreur -- Impossible d'ouvrir le fichier %s\n", pathFichier);
        exit(EXIT_FAILURE);
    }
    free(pathFichier);
    return true;
}
   





/**
 * La fonction affiche_debut affiche la mise en page de l'analyseur SLR
 * @param tailleMot taille du mot a analyser
 */
void affichage_debut(int tailleMot)
{
    printf("\n\n   ");
    for (int i = 0; i < tailleMot - 1; i++)
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
    int diff = tailleMot - strlen(flot) +1;
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

