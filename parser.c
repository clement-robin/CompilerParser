/* Auteur : Clement ROBIN & Lucas DESHAYES */

#include "outils.h"
#include "arbre.h"


int main(int argc, char const *argv[])
{
    /*** VARIABLES ***/
    int tailleMot;
    int taillePile = 1;
    int tailleNeoudsParcourus;

    char caractereRetire;
    char caractereNonTerminal;
    char noeudActuel;

    char * pathFichier;
    char * mot;
    char * flot;
    char * pile = (char * )malloc(1 * sizeof(char));
    char * transition = (char *)malloc(3 * sizeof(char));
    
    arbre ** neoudsRencontresOrphelins;
    file_read analyseurLR;



    /*** VERIFICATION : bon nombre d'arguments ? -> 3 attendus ***/
    printf("Validation du nombre d'arguments en cours ...\n");
    if(argc < 3) {
        printf("--> erreur -- trop peu d'arguments (tableau SLR et mot a tester requis)\n");
        exit(EXIT_FAILURE);

    }
    else if(argc > 3) {
        printf("--> erreur -- trop d'arguments (tableau SLR et mot a tester requis)\n");
        for(int i = 3; i < argc; i++) {
            printf("          %s <-- argument en trop\n",argv[i]);
        }
        exit(EXIT_FAILURE);
    }
    printf("--> Le nombre d'arguments est conforme\n");


    /*** VERIFICATION : le fichier existe ? (dans assets/) ***/
    printf("Validation du fichier %s en cours ...\n",argv[1]);

    pathFichier = (char * )malloc(strlen(argv[1])+1 * sizeof(char));
    strcpy( pathFichier, argv[1]);
    
    FILE* file = fopen(pathFichier, "r+");
    
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
        fprintf(stderr,"--> erreur -- Impossible d'ouvrir le fichier %s\n",pathFichier);
        exit(EXIT_FAILURE);

    }

    /*** VERIFICATION : le mot est valide ? ***/
    printf("Validation du mot en cours ...\n");
    tailleMot = strlen(argv[2])+1;
    mot = (char * )malloc(tailleMot * sizeof(char));
    strcpy(mot, argv[2]);
    printf("--> Le mot \"%s\" est valide\n\n",mot);

    // Affichage des 2 parametres valides
    printf("Analyseur SLR sur la table %s avec le mot \"%s\" :\n",pathFichier,mot);



    /*********************************/
    /*** DEBUT DE L'ALGORITHME SLR ***/
    /*********************************/

    
    // Initialistion 
    flot = (char * )malloc(tailleMot+1 * sizeof(char));
    strcpy(flot,mot);
    strcpy(pile,"0");
    strcpy(transition,"  ");
    neoudsRencontresOrphelins = (arbre **)malloc(strlen(mot) * 512 * sizeof(arbre *));



    // Affichage du tableau et de la 1er ligne
    affichage_debut(tailleMot);
    affichage_ligne(transition, flot, pile, tailleMot);

    // recuperation de la 1ere valeur de transition dans le tableau
    signed char valeurTransition = analyseurLR.t.trans[(signed char)mot[0]];

    // boucle qui s'arrete si la valeur de transition est une erreur ou une acceptation
    while(pile[0]=='0')
    {

        /*** cas d'une erreur (le mot c'est pas reconnu) ***/
        if (valeurTransition == 0) {
            pile = "err";

            //arbre
            noeudActuel = 0;
        }
        /*** cas d'une acceptation (le mot est reconnu) ***/
        else if(valeurTransition == -127){ 
            pile = "acc";

            //arbre
            noeudActuel = 0;
        }
        /*** cas du decalage ***/
        else  if(valeurTransition > 0) {

            //arbre
            noeudActuel = flot[0];
            arbre* terminal = (arbre *)malloc(sizeof(arbre));
            terminal->nombreFils = 0;
            terminal->valeur = noeudActuel;
            
            neoudsRencontresOrphelins[tailleNeoudsParcourus] = terminal;
            tailleNeoudsParcourus++;

            // valeur de la transition
            transition[0] = 'd';
            transition[1] = valeurTransition + '0';
            
            // on retire le 1er element du flot
            caractereRetire = flot[0];
            if (strcmp(flot,"\0") != 0)
                memmove(flot, flot + 1, strlen(flot));

            // on ajoute a la pile l'element retire 
            taillePile += 2;
            pile = (char *) realloc( pile , taillePile * sizeof(char));
            pile[taillePile-2] = caractereRetire;

            // puis on ajoute a la pile la valeur de reduction
            pile[taillePile-1] = valeurTransition + '0';
            pile[taillePile] = '\0';
        }
        /*** cas d'une reduction ***/
        else if(valeurTransition < 0) {

            //arbre
            noeudActuel = analyseurLR.G.rules[-valeurTransition - 1].lhs;
            arbre * nonTerminal = (arbre*)malloc(sizeof(arbre));
            nonTerminal->valeur = noeudActuel;
            nonTerminal->nombreFils = 0;

            int nbRightElement = strlen((const char*)analyseurLR.G.rules[-valeurTransition - 1].rhs);
            while (nbRightElement!=0)
            {
                nonTerminal->fils[nonTerminal->nombreFils] = neoudsRencontresOrphelins[tailleNeoudsParcourus-nbRightElement];
                nonTerminal->nombreFils++;
                nbRightElement--;
            }
            tailleNeoudsParcourus -= strlen((const char*)analyseurLR.G.rules[-valeurTransition - 1].rhs);
            neoudsRencontresOrphelins[tailleNeoudsParcourus] = nonTerminal;
            tailleNeoudsParcourus++;

            // valeur de la transition
            transition[0] = 'r';
            transition[1] = -valeurTransition + '0';

            //Symbole non terminal de la regle 
            caractereNonTerminal = analyseurLR.G.rules[-valeurTransition-1].lhs;

            /*** cas d'une transition en Epsilon (S: ) ***/
            if (strlen((signed char)analyseurLR.G.rules[-valeurTransition-1].rhs)==0) {
                // le flot ne change pas
                // on ajoute a la pile le caractere non terminal correspondant
                taillePile += 2;
                pile = (char *) realloc( pile , taillePile * sizeof(char) );
                
                // puis on ajoute a la pile la valeur de reduction
                pile[taillePile-2] = caractereNonTerminal;
                pile[taillePile-1] = analyseurLR.t.trans[256 *(pile[taillePile-3]-'0'+1)  - analyseurLR.G.rules[-valeurTransition-1].lhs]+'0';

            }
            /*** cas d'une transition avec un caractere non terminal (exemple S: a$Sb) ***/
            else {
                // le flot ne change pas
                // on cherche le nombre de caractere de la regle reconnu
                int nbCaractereRegle = strlen(analyseurLR.G.rules[-valeurTransition-1].rhs);


                // on retire la regle de la pile
                taillePile = taillePile -(2*(nbCaractereRegle-1));
                pile = (char *) realloc( pile , taillePile * sizeof(char) );

                // on ajoute a la pile le caractere non terminal correspondant + la valeur de reduction 
                pile[taillePile-2] = caractereNonTerminal;
                pile[taillePile-1] = analyseurLR.t.trans[256 *(pile[taillePile-3]-'0'+1)  - analyseurLR.G.rules[-valeurTransition-1].lhs]+'0';
                pile[taillePile] = '\0';
            }
        }
        

        // recuperation de la nouvelle valeur de transition dans le tableau
        valeurTransition = analyseurLR.t.trans[256 *(pile[taillePile-1]-'0') + flot[0]];

        // Affiche de la ligne selon la transiton, le flot, la pile et la taille du mot
        affichage_ligne(transition, flot, pile, tailleMot);
        if (strcmp(pile,"acc") == 0) {
            printf("\n\n");
            affichage_arbre(neoudsRencontresOrphelins[0]);
        }
    }


    /*******************************/
    /*** FIN DE L'ALGORITHME SLR ***/
    /*******************************/

    printf("\n\n");

    free(flot);
    free(mot);
    free(pathFichier);
    //free(pile);
    free_arbre(neoudsRencontresOrphelins[0]);
    free(neoudsRencontresOrphelins);

    return 0;
}

