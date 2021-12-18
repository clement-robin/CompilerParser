#include "grammaire.h"

int main(int argc, char *argv[]) {

    for (int i = 1; i < argc; i++) {
        printf("argv[%d] = %s\n\n", i, argv[i]);
    
        FILE* fichier = NULL;
        int caractereActuel = 0;

        fichier = fopen(argv[i], "r+");



        if (fichier != NULL)
        {
            // Boucle de lecture des caractères un à un
            do
            {
                caractereActuel = fgetc(fichier); // On lit le caractère
                printf("%c", caractereActuel); // On l'affiche
            } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
    
            fclose(fichier);
        }
        else
        {
            // On affiche un message d'erreur si on veut
            printf("Impossible d'ouvrir le fichier test.txt");
        }
 
    }
    return 0;
 }