#include "outils.h"


int main(int argc, char const *argv[])
{
    // Variables
    int sizeMot;
    int sizePile = 1;
    char * pathFichier;
    char * mot;
    char * flot;
    char * pile = (char * )malloc(1 * sizeof(char));
    char * transition = (char * )malloc(2 * sizeof(char));
    char caractereRetire;
    file_read analyseurLR;

    
    // Verification du bon nombre d'arguments
    if(argc < 3) {
        printf("erreur -- trop peu d'arguments (tableau SLR et mot a tester requis)\n");
        exit(EXIT_FAILURE);

    }
    else if(argc > 3) {
        printf("erreur -- trop d'arguments (tableau SLR et mot a tester requis)\n");
        for(int i = 3; i < argc; i++) {
            printf("          %s <-- argument en trop\n",argv[i]);
        }
        exit(EXIT_FAILURE);
    }

    // Verification de l'existance du fichier (dans assets/) 
    pathFichier = (char * )malloc(strlen(argv[1])+1 * sizeof(char));
    strcpy( pathFichier, argv[1]);
    
    FILE* file = fopen(pathFichier, "r+");
    printf("\nValidation du fichier en cours ...\n");

    if (file != NULL)
    {
        printf("--> Le fichier %s existe\n",pathFichier);
        
        // Verification si le fichier est lisible par read_file
        analyseurLR = read_file(pathFichier);
        printf("--> Le fichier %s est bien lu\n",pathFichier);
        fclose(file);
    }
    else
    {
        fprintf(stderr,"--> Impossible d'ouvrir le fichier %s\n",pathFichier);
        exit(EXIT_FAILURE);

    }

    // Verification si le mot est valide 
    printf("Validation du mot en cours ...\n");
    sizeMot = strlen(argv[2])+1;
    mot = (char * )malloc(sizeMot * sizeof(char));
    strcpy(mot, argv[2]);
    printf("--> Le mot \"%s\" est valide\n\n",mot);

    // Affichage des 2 parametres valides
    printf("Analyseur SLR sur la table %s avec le mot \"%s\" :\n",pathFichier,mot);

    // Initialistion du flot et de la pile
    flot = (char * )malloc(sizeMot * sizeof(char));
    strcpy(flot,mot);
    strcpy(pile,"0");
    strcpy(transition,"  ");

    // Affichage du tableau et de la 1er ligne
    affichage_debut(sizeMot);
    affichage_ligne(transition, flot, pile, sizeMot);

    // recuperation de la valeur de transition dans le tableau
    signed char valeurTransition = analyseurLR.t.trans[mot[0]];

    // boucle qui s'arrete si la valeur de transition est une erreur ou une acceptation
    for (int i = 0; i < 4; i++)
    {
        /*** cas du decalage ***/
        if(valeurTransition > 0) {

            // valeur de la transition
            transition[0] = 'd';
            transition[1] = valeurTransition + '0';
            
            // on retire le 1er element du flot
            caractereRetire = flot[0];
            if (strcmp(flot,"\0") != 0)
                memmove(flot, flot + 1, strlen(flot));

            // on ajoute a la pile l'element retire + la valeur de reduction
            sizePile += 2;
            pile = (char *) realloc( pile , sizePile * sizeof(int) );

            pile[sizePile-2] = caractereRetire;
            pile[sizePile-1] = valeurTransition + '0';
        }
        /*** cas d'une acceptation (le mot est reconnu) ***/
        else if(valeurTransition == -127){ 
            pile = "acc";
        }
        /*** cas d'une reduction ***/
        else if(valeurTransition < 0) { 

            // valeur de la transition
            transition[0] = 'r';
            transition[1] = -valeurTransition + '0';

            /*** cas d'une transition en Epsilon (S: ) ***/
            if (strlen(analyseurLR.G.rules[-valeurTransition-1].rhs)==0) {
                //le flot ne change pas
                // on ajoute S puis la valeur de la transtion a la pile
                sizePile += 2;
                pile = (char *) realloc( pile , sizePile * sizeof(int) );

                pile[sizePile-2] = analyseurLR.G.rules[-valeurTransition-1].lhs;
                pile[sizePile-1] = analyseurLR.t.trans[256 *(pile[sizePile-3]-'0'+1)  - analyseurLR.G.rules[-valeurTransition-1].lhs]+'0';
            }
            /*** cas d'une transition avec un caractere non terminal (exemple S: a$Sb) ***/
            else {
                // le flot ne change pas
                // on cherche a reconnaitre la regle dans la pile
                //char temp = strlen(fichierLu.G.rules[-transMot-1].rhs);

                // on retire la regle de la pile

                // on ajoute a la pile le caractere non terminal correspondant + la valeur de reduction 
            }

        }
        /*** cas d'une erreur (le mot c'est pas reconnu) ***/
        else if (valeurTransition == 0) {
            pile = "err";
        }
        
        affichage_ligne(transition, flot, pile, sizeMot);

        valeurTransition = analyseurLR.t.trans[256 *(pile[sizePile-1]-'0') + flot[0]];
        //printf("valeurTransition : |%d|\n",valeurTransition);
    }


    free(pathFichier);
    free(pile);
    free(flot);
    free(mot);
    free(transition);

    printf("\n\n");

    return 0;
}

