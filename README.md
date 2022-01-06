# CompilerParser

Projet d’Algorithmes pour la compilation (IATIC 4 - ISTY)


Ce projet à pour but d'implémenter un analyseur SLR.
A l'execution, l'executable prend 2 arguments :
- le fichier contenant les règles de grammaire ainsi que la table LR
- un mot à test qui peut être accepté ou refusé par la grammaire

Le programme affiche alors l'analyseur LR correspondant avec, ligne par ligne, l'action, le flot et la pile. De plus, is le mot est accepter par la grammaire, le programme affiche aussi l'arbre d'analyse.

## Contenu

### Fichiers test :
Fourni avec le sujet, ces tableaux LR et leurs règles nous permettent de tester si des mots sont accepté par la grammaire ou non. Ces fichiers sont :
- **test**
- **test2** 
- **test3**
- **test4**
- **test5** (que nous avons ajouté pour tester une exception)

### Dossier /sources :
Fourni avec le sujet, les fichiers qui structures les tableaux selon leurs grammaires et les règles qu'elle contient en structures c sont :
- **read_file.c** (et **read_file.h**)
- **LRGrammar.c** (et **LRGrammar.h**)

A cela, nous avons développer la partie de l'analyseur LR.
Le main se situe dans le fichier :
- **parser.c**

La structure des arbres d'analyse ainsi que des fonctions associés sont dans les fichiers :
- **arbre.c** (et **arbre.h**)

Enfin, des fonctions utiles pour notre projet se trouvent dans les fichiers :
- **outils.c** (et **outils.h**)

## Compilation

Nous compilons notre projet dans le **makefile** avec la commande : 

```bash
$ make
```

Ensuite, afin de l'executer, on utilise la commande suivant avec les 2 arguments requis (fichier contenant la grammaire et un mot) :
 

```bash
$ ./LRanalyzer file "word"
```

### Exemple de complilation

- Avec la grammaire suivant fourni dans le fichier **test** :
```textarea
S:a\$Sb
S:
	a	b	\$	S
0	d2	r2	r2	1
1			a
2	d2	r2	r2	3
3		d4
4		r1	r1
```
- Avec l'execution suivante :
```bash
$ ./LRanalyzer test "ab"
```

- Le résultat est :
```testarea
Analyseur SLR sur la table test avec le mot "ab" :


     Flot  |   Pile
  ------------------------------
        ab | 0
d2       b | 0a2
r2       b | 0a2S3
d4         | 0a2S3b4
r1         | 0S1
          accept

S(a()S()b())
```