/* Auteurs : Clement ROBIN & Lucas DESHAYES */

#include "outils.h"

/******* FONCTIONS ******/


/**
 * La fonction verification_nombre_arguments verifie si le bon nombre d'arguments sont donne a l'execution 
 * soit 3 : l'executable, le fichier et le mot
 * @param argc 
 * @param argv 
 */
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

/**
 * La fonction verification_fichier permet de verifier si un fichier existe bien dans son path
 * puis de verifier s'il l'on le lire avec read_file
 * @param fichier fichier que l'on souhaite verifier
 * @param analyseurLR strucure de grammaire qui dont convenir a la bon execution
 * @return true la verification vest valide
 * @return false la verfication a echoue
 */
bool verification_fichier(const char *fichier, file_read analyseurLR)
{
    /*** VERIFICATION : le fichier existe ? (dans assets/) ***/
    char *pathFichier = (char *)malloc(strlen(fichier) + 1 * sizeof(char));
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
    int valeurAction;
    if (strcmp(pile, "acc") == 0 || strcmp(pile, "ref") == 0)
        printf("  ");
    else
    {
        valeurAction = val[1] - '0';
        if (valeurAction >= 10)
        {
            val[1] = valeurAction / 10 + '0';
            val[2] = valeurAction % 10 + '0';
            val[3] = '\0';
            espace = 1;
        }
        else
        {
            val[2] = '\0';
        }
        printf("%s", val);
    }
    int diff = tailleMot - strlen(flot) + 1;
    for (int i = 0; i < 4 + diff - espace; i++)
    {
        printf(" ");
    }
    if (strcmp(pile, "acc") == 0)
        printf("accept");
    else if (strcmp(pile, "ref") == 0)
        printf("refuse");
    else
    {
        int compteur = 0;
        while (pile[compteur] != '\0')
        {
            compteur++;
        }
        valeurAction = pile[compteur - 1] - '0';
        if (valeurAction >= 10)
        {

            char *buffer = (char *)malloc((compteur + 3) * sizeof(char));
            strcpy(buffer, pile);

            buffer[compteur - 1] = valeurAction / 10 + '0';
            buffer[compteur] = valeurAction % 10 + '0';
            buffer[compteur + 1] = '\0';
            printf("%s | %s\n", flot, buffer);
        }
        else
        {
            printf("%s | %s\n", flot, pile);
        }
    }
}
