/* Author : Clement ROBIN & Lucas DESHAYES */

#include "outils.h"


int main(int argc, char const *argv[])
{
    /*** VARIABLES ***/
    int sizeMot;
    int sizePile = 1;
    char * pathFichier;
    char * mot;
    char * flot;
    char * pile = (char * )malloc(1 * sizeof(char));
    char * transition = (char * )malloc(2 * sizeof(char));
    char * listeRegle = (char * )malloc(100 * sizeof(char));
    char caractereRetire;
    char caractereNonTerminal;
    file_read analyseurLR;

    /*** VERIFICATION : bon nombre d'arguments ? -> 3 attendus ***/
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
    /*** VERIFICATION : le fichier existe ? (dans assets/) ***/
    pathFichier = (char * )malloc(strlen(argv[1])+1 * sizeof(char));
    strcpy( pathFichier, argv[1]);
    
    FILE* file = fopen(pathFichier, "r+");
    printf("\nValidation du fichier en cours ...\n");

    if (file != NULL)
    {
        printf("--> Le fichier %s existe\n",pathFichier);
        
        /*** VERIFICATION : le fichier est lisible par read_file ? ***/
        analyseurLR = read_file(pathFichier);
        printf("--> Le fichier %s est bien lu\n",pathFichier);
        fclose(file);
    }
    else
    {
        fprintf(stderr,"--> Impossible d'ouvrir le fichier %s\n",pathFichier);
        exit(EXIT_FAILURE);

    }

    /*** VERIFICATION : le mot est valide ? ***/
    printf("Validation du mot en cours ...\n");
    sizeMot = strlen(argv[2])+1;
    mot = (char * )malloc(sizeMot * sizeof(char));
    strcpy(mot, argv[2]);
    printf("--> Le mot \"%s\" est valide\n\n",mot);


    /*********************************/
    /*** DEBUT DE L'ALGORITHME SLR ***/
    /*********************************/

    // Affichage des 2 parametres valides
    printf("Analyseur SLR sur la table %s avec le mot \"%s\" :\n",pathFichier,mot);

    // Initialistion du flot, de la pile
    flot = (char * )malloc(sizeMot * sizeof(char));
    strcpy(flot,mot);
    strcpy(pile,"0");
    strcpy(transition,"  ");
    strcpy(listeRegle,"");

    // Affichage du tableau et de la 1er ligne
    affichage_debut(sizeMot);
    affichage_ligne(transition, flot, pile, sizeMot);

    // recuperation de la 1ere valeur de transition dans le tableau
    signed char valeurTransition = analyseurLR.t.trans[mot[0]];

    // boucle qui s'arrete si la valeur de transition est une erreur ou une acceptation
    while(strcmp(pile,"acc") != 0 && strcmp(pile,"err") != 0)
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

            // on ajoute a la pile l'element retire 
            sizePile += 2;
            pile = (char *) realloc( pile , sizePile * sizeof(char) );
            pile[sizePile-2] = caractereRetire;

            // puis on ajoute a la pile la valeur de reduction
            pile[sizePile-1] = valeurTransition + '0';
            pile[sizePile] = '\0';

            // liste
            char * buffer = (char *) malloc(strlen(listeRegle));
            char * ajout = (char *) malloc(3);
    
            ajout[0] = caractereRetire;
            ajout[1] = '(';
            ajout[2] = ')';
            ajout[3] = '\0';
            strcat(strcpy(buffer, ajout), listeRegle);
            listeRegle = buffer;
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

            //Symbole non terminal de la regle 
            caractereNonTerminal = analyseurLR.G.rules[-valeurTransition-1].lhs;


            /*** cas d'une transition en Epsilon (S: ) ***/
            if (strlen(analyseurLR.G.rules[-valeurTransition-1].rhs)==0) {
                // le flot ne change pas
                // on ajoute a la pile le caractere non terminal correspondant
                sizePile += 2;
                pile = (char *) realloc( pile , sizePile * sizeof(char) );
                
                // puis on ajoute a la pile la valeur de reduction
                pile[sizePile-2] = caractereNonTerminal;
                pile[sizePile-1] = analyseurLR.t.trans[256 *(pile[sizePile-3]-'0'+1)  - analyseurLR.G.rules[-valeurTransition-1].lhs]+'0';
            }
            /*** cas d'une transition avec un caractere non terminal (exemple S: a$Sb) ***/
            else {
                // le flot ne change pas
                // on cherche le nombre de caractere de la regle reconnu
                int nbCaractereRegle = strlen(analyseurLR.G.rules[-valeurTransition-1].rhs);

                // on retire la regle de la pile
                sizePile = sizePile -(2*(nbCaractereRegle-1));
                pile = (char *) realloc( pile , sizePile * sizeof(char) );

                // on ajoute a la pile le caractere non terminal correspondant + la valeur de reduction 
                pile[sizePile-2] = caractereNonTerminal;
                pile[sizePile-1] = analyseurLR.t.trans[256 *(pile[sizePile-3]-'0'+1)  - analyseurLR.G.rules[-valeurTransition-1].lhs]+'0';
                pile[sizePile] = '\0';


            }
            
            // ajout a la liste 
            char * buffer = (char *) malloc(strlen(listeRegle));
            char * ajoutDebut = (char *) malloc(2);

    
            ajoutDebut[0] = caractereNonTerminal;
            ajoutDebut[1] = '(';
            ajoutDebut[2] = '\0';

    
            strcat(strcpy(buffer, ajoutDebut), listeRegle);
            strcat(buffer, ")");
            listeRegle = buffer;
            //S(a()S(a()S(a()S(a()S()b())b())b())b())
        }
        /*** cas d'une erreur (le mot c'est pas reconnu) ***/
        else if (valeurTransition == 0) {
            pile = "err";
        }

        // recuperation de la nouvelle valeur de transition dans le tableau
        valeurTransition = analyseurLR.t.trans[256 *(pile[sizePile-1]-'0') + flot[0]];

        // Affiche de la ligne selon la transiton, le flot, la pile et la taille du mot
        affichage_ligne(transition, flot, pile, sizeMot);
        if (strcmp(pile,"acc") == 0) {
                printf("\n\n%s\n\n",listeRegle);

        }
    }


    /*******************************/
    /*** FIN DE L'ALGORITHME SLR ***/
    /*******************************/

    printf("\n\n");

    return 0;
}

