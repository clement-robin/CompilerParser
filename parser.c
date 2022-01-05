/* Auteurs : Clement ROBIN & Lucas DESHAYES */

#include "outils.h"
#include "arbre.h"

int main(int argc, char const *argv[])
{
    /*** VARIABLES ***/
    int tailleMot;
    int taillePile = 1;
    int nombreFilsArbreParcourus = 0;

    char caractereRetire;
    char caractereNonTerminal;
    char caractereArbreActuel;

    signed char valeurAction;

    char * mot;
    char * flot;
    char * pile;
    char * action;

    arbre **listeArbresFils;
    file_read analyseurLR;

    // Vererifications
    printf("Validation du nombre d'arguments en cours ...\n");
    verification_nombre_arguments(argc, argv);
    printf("--> Le nombre d'arguments est conforme\n");

    printf("Validation du fichier %s en cours ...\n", argv[1]);
    if(verification_fichier(argv[1], analyseurLR))
        analyseurLR = read_file(argv[1]);

    // Le mot est valide ?
    tailleMot = strlen(argv[2]) + 1;
    printf("Validation du mot en cours ...\n");
    mot = (char *)malloc(tailleMot * sizeof(char));
    strcpy(mot, argv[2]);
    printf("--> Le mot \"%s\" est valide\n\n", mot);

    // Affichage des 2 parametres valides
    printf("Analyseur SLR sur la table %s avec le mot \"%s\" :\n", argv[1], mot);

    /*********************************/
    /*** DEBUT DE L'ALGORITHME SLR ***/
    /*********************************/

    // Initialistion des variables
    pile = (char *)malloc(taillePile + 1 * sizeof(char));   // 0 + '\0'
    flot = (char *)malloc(tailleMot + 1 * sizeof(char));    // taille du mot + '\0'
    action = (char *)malloc(3 * sizeof(char));              // r ou d + valeur + '\0'
    strcpy(flot, mot);
    strcpy(pile, "0");
    strcpy(action, "  ");

    // Initialistion des variables pour l'arbre
    listeArbresFils = (arbre **)malloc(strlen(mot) * TAILLEMAX * sizeof(arbre *));
    arbre *arbreVide = (arbre *)malloc(sizeof(arbre));
    arbreVide->nombreFils = 0;
    listeArbresFils[0] = arbreVide;

    // Affichage du tableau et de la 1er ligne
    affichage_debut(tailleMot);
    affichage_ligne(action, flot, pile, tailleMot);

    // Recuperation de la 1ere valeur de action dans le tableau
    valeurAction = analyseurLR.t.trans[(signed char)flot[0]];

    // Boucle qui s'arrete si la valeur de l'action est une erreur ou une acceptation
    while (pile[0] == '0')
    {

        /*** cas d'une erreur (le mot c'est pas reconnu) ***/
        if (valeurAction == 0)
        {
            strcpy(pile, "err");
        }
        /*** cas d'une acceptation (le mot est reconnu) ***/
        else if (valeurAction == -127)
        {
            strcpy(pile, "acc");
        }
        /*** cas du decalage ***/
        else if (valeurAction > 0)
        {

            // initialisation de l'arbre fils
            caractereArbreActuel = flot[0];
            arbre *terminal = (arbre *)malloc(sizeof(arbre));
            terminal->nombreFils = 0;
            terminal->valeur = caractereArbreActuel;

            // on va ajouter en tant que fils
            listeArbresFils[nombreFilsArbreParcourus] = terminal;
            nombreFilsArbreParcourus++;

            // valeur de l'action
            action[0] = 'd';
            action[1] = valeurAction + '0';

            // on retire le 1er element du flot
            caractereRetire = flot[0];
            if (strcmp(flot, "\0") != 0)
                memmove(flot, flot + 1, strlen(flot));

            // on ajoute a la pile l'element retire
            taillePile += 2;
            pile = (char *)realloc(pile, taillePile * sizeof(char));
            pile[taillePile - 2] = caractereRetire;

            // puis on ajoute a la pile la valeur de reduction
            pile[taillePile - 1] = valeurAction + '0';
            pile[taillePile] = '\0';
        }
        /*** cas d'une reduction ***/
        else if (valeurAction < 0)
        {
            // arbre : on va ajouter un nouveau fils pour la reduction correspondante
            // initialisation de l'arbre fils
            caractereArbreActuel = analyseurLR.G.rules[-valeurAction - 1].lhs;
            arbre *arbreFils = (arbre *)malloc(1 * sizeof(arbre));
            arbreFils->valeur = caractereArbreActuel;
            arbreFils->nombreFils = 0;

            // on remplit l'arbre fils
            int nombreElementsCorrects = strlen((const char *)analyseurLR.G.rules[-valeurAction - 1].rhs);
            while (nombreElementsCorrects != 0)
            {
                arbreFils->fils[arbreFils->nombreFils] = listeArbresFils[nombreFilsArbreParcourus - nombreElementsCorrects];
                arbreFils->nombreFils++;
                nombreElementsCorrects--;
            }

            // on ajoute l'arbre fils à l'arbre
            nombreElementsCorrects = strlen((const char *)analyseurLR.G.rules[-valeurAction - 1].rhs);
            nombreFilsArbreParcourus = nombreFilsArbreParcourus - nombreElementsCorrects;
            listeArbresFils[nombreFilsArbreParcourus] = arbreFils;
            nombreFilsArbreParcourus++;

            // valeur de l'action
            action[0] = 'r';
            action[1] = -valeurAction + '0';

            // Symbole non terminal de la regle
            caractereNonTerminal = analyseurLR.G.rules[-valeurAction - 1].lhs;

            /*** cas d'une regle en Epsilon (exemple S: ) ***/
            if (nombreElementsCorrects == 0)
            {
                // le flot ne change pas
                // on ajoute a la pile le caractere non terminal correspondant
                taillePile += 2;
                pile = (char *)realloc(pile, taillePile * sizeof(char));

                // puis on ajoute a la pile la valeur de reduction
                pile[taillePile - 2] = caractereNonTerminal;
                pile[taillePile - 1] = analyseurLR.t.trans[256 * (pile[taillePile - 3] - '0' + 1) - analyseurLR.G.rules[-valeurAction - 1].lhs] + '0';
                pile[taillePile] = '\0';
            }
            /*** cas d'une regle avec un caractere non terminal (exemple S:a$Sb) ***/
            else
            {
                // le flot ne change pas
                // on cherche le nombre de caractere de la regle reconnu
                int nbCaractereRegle = strlen((const char *)analyseurLR.G.rules[-valeurAction - 1].rhs);

                // on retire la regle de la pile
                taillePile = taillePile - (2 * (nbCaractereRegle - 1));
                pile = (char *)realloc(pile, taillePile * sizeof(char));

                // on ajoute a la pile le caractere non terminal correspondant + la valeur de reduction
                pile[taillePile - 2] = caractereNonTerminal;
                pile[taillePile - 1] = analyseurLR.t.trans[256 * (pile[taillePile - 3] - '0' + 1) - analyseurLR.G.rules[-valeurAction - 1].lhs] + '0';
                pile[taillePile] = '\0';
            }
        }

        // recuperation de la nouvelle valeur de action dans le tableau
        valeurAction = analyseurLR.t.trans[TAILLEMAX * (pile[taillePile - 1] - '0') + flot[0]];

        // Affiche de la ligne selon la transiton, le flot, la pile et la taille du mot
        affichage_ligne(action, flot, pile, tailleMot);
        if (strcmp(pile, "acc") == 0)
        {
            printf("\n\n");
            affichage_arbre(listeArbresFils[0]);
        }
        
    }
    printf("\n\n");

    /*******************************/
    /*** FIN DE L'ALGORITHME SLR ***/
    /*******************************/

    free(flot);
    free(mot);
    free(pile);
    if (listeArbresFils[0] != 0)
        free_arbre(listeArbresFils[0]);
    else
        free(listeArbresFils[0]);

    free(listeArbresFils);

    return 0;
}
