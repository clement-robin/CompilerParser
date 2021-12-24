#include "outils.h"


int main(int argc, char const *argv[])
{
    int sizeMot;
    char * pathFichier;
    char * mot;
    char * flot;
    char * pile;
    char * transition = (char * )malloc(2 * sizeof(char));
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
    printf("Validation du fichier en cours ...\n");

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
    printf("Validation du en cours ...\n");
    sizeMot = strlen(argv[2])+1;
    mot = (char * )malloc(sizeMot * sizeof(char));
    strcpy(mot, argv[2]);
    printf("--> Le mot est valide ");

    printf("\n\nFichier : %s\nMot : %s\n",pathFichier,mot);

    // Initialistion du flot et de la pile
    flot = (char * )malloc(sizeMot * sizeof(char));
    strcpy(flot,mot);
    pile = (char * )malloc(sizeMot * sizeof(char));
    strcpy(pile,"0");
    strcpy(transition,"  ");

    affichage_debut(sizeMot);
    affichage_ligne(transition, flot, pile, sizeMot);

    signed char transMot = analyseurLR.t.trans[256 * 0 + mot[0]];
    if(transMot + '0' > 0) {
        // valeur de la transition
        transition[0] = 'd';
        transition[1] = transMot + '0';

        // on retire le 1er element du flot
        char caractereRetire = flot[0];
        if (flot[0]!='\0')
            memmove(flot, flot + 1, strlen(flot));

        // on ajoute a la pile l'element retire + la valeur de reduction
        int taillepile = strlen(pile);
        pile[taillepile] = caractereRetire;
        pile[taillepile+1] = transMot + '0';
        pile[taillepile+2] = '\0';
    }
    else if(transMot + '0' == -127){
        pile = "acc";
    }
    else if(transMot + '0' < 0) {
        printf("char : |r%c|", transMot + '0');
        transition[0] = 'r';
        transition[1] = transMot + '0';
        printf("transition : |%s|",transition);

    }
    else if (transMot + '0' == 0) {
        pile = "err";
    }
    


    affichage_ligne(transition, flot, pile, sizeMot);

    

    //void affichage_ligne(transition, flot, pile, sizeMot);


    printf("\n\n\n");

    return 0;
}

