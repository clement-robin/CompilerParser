/* Auteur : Clement ROBIN & Lucas DESHAYES */

#include "arbre.h"

/******* FONCTIONS ******/

/**
 *  
 * 
 * @param racine 
 */
void print_arbre(arbre *racine){
    printf("%c(",racine->valeur);
    for (int i = 0; i < racine->nombreFils; i++)
    {
        print_arbre(racine->fils[i]);
    }
    printf(")");
};

/**
 * 
 * 
 * @param racine 
 */
void free_arbre(arbre *racine){
    if (racine != NULL) {
        for (size_t i = 0; i < racine->nombreFils; i++)
        {
            free_arbre(racine->fils[i]);
        }
        free(racine);
    }
};

/**
 *  
 * 
 * @param caractereLu 
 * @param transition 
 * @param parGrammar 
 * @return char 
 */
char recup_node(char caractereLu, char transition, grammar parGrammar){
    if (transition==-127) // accept
    {
        return 0;
    }
    else if (transition>0) // decalage
    {
        return caractereLu;
    } else if (transition<0) // reduciton
    {
        return parGrammar.rules[-transition - 1].lhs;
    }
    return 0; // erreur
}

/**
 * 
 * 
 * @param nodeRecup 
 * @param transition 
 * @param parGrammar 
 */
void construire_arbre(char nodeRecup, signed char transition, grammar parGrammar)
{
    if (nodeRecup==0) // accept ou erreur
    {
        return;
    }
    
    if (transition<0) // reduction
    {
        arbre *nonTerminal = (arbre*)malloc(sizeof(arbre));
        nonTerminal->valeur = nodeRecup;
        nonTerminal->nombreFils = 0;

        int nbRightElement = strlen((const char*)parGrammar.rules[-transition - 1].rhs);
        while (nbRightElement!=0)
        {
            nonTerminal->fils[nonTerminal->nombreFils] = neoudsRencontresOrphelins[tailleNeoudsRencontresOrphelins-nbRightElement];
            nonTerminal->nombreFils++;
            nbRightElement--;
        }
        tailleNeoudsRencontresOrphelins -= strlen((const char*)parGrammar.rules[-transition - 1].rhs);
        neoudsRencontresOrphelins[tailleNeoudsRencontresOrphelins] = nonTerminal;
        tailleNeoudsRencontresOrphelins++;
    }
    else if (transition>0) // decalage
    {
        arbre* terminal = (arbre *)malloc(sizeof(arbre));
        terminal->nombreFils = 0;
        terminal->valeur = nodeRecup;
        
        neoudsRencontresOrphelins[tailleNeoudsRencontresOrphelins] = terminal;
        tailleNeoudsRencontresOrphelins++;
    }
}
