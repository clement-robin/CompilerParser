#include "outils.h"


int main(int argc, char const *argv[])
{
    char* fichier;
    char* mot;
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

    fichier = (char * )malloc(strlen(argv[1])+1);
    strcpy( fichier, argv[1]);
    
    FILE* file = fopen(fichier, "r+");
    printf("Validation du fichier en cours ...\n");

    if (file != NULL)
    {
        printf("--> Le fichier %s existe\n",fichier);
        
        // Verification si le fichier est lisible par read_file
        analyseurLR = read_file(fichier);
        printf("--> Le fichier %s est bien lu\n",fichier);
        fclose(file);
    }
    else
    {
        fprintf(stderr,"--> Impossible d'ouvrir le fichier %s\n",fichier);
        exit(EXIT_FAILURE);

    }

    // Verification si le mot est valide 
    printf("Validation du en cours ...\n");
    mot = (char * )malloc(strlen(argv[2])+1);
    strcpy( mot, argv[2]);
    printf("--> Le mot est valide ");

    printf("\n\nFichier : %s\nMot : %s\n",fichier,mot);

    affichage_debut(strlen(mot));
    char * flot = mot;
    char * pile = "0";

    char * val = "d2";

    affichage_ligne(val,flot,pile,strlen(mot));

    flot = "bc";
    affichage_ligne(val,flot,pile,strlen(mot));

    flot = "c";
    affichage_ligne(val,flot,pile,strlen(mot));

    flot = "";
    pile ="acc";
    affichage_ligne(val,flot,pile,strlen(mot));

    printf("\n\n\n");

    

    // tester et la pile / float et 





    /*print("marwane : %s",marwane.G.rules[0].rhs);
    print_grammar(marwane.G);
    print_table(marwane.t,marwane.G);*/

    return 0;
}

