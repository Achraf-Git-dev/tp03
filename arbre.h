#ifndef ARBRE__H
#define ARBRE__H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct arbre
{
    char contenu;
    struct arbre* lv;
    struct arbre* lh;
} arbre_t;

arbre_t* NotAlgEnArbre(char* notation);
arbre_t* Ajouter(arbre_t** arbre, char a_ajouter);
void AfficherDictionnaire(arbre_t* arbre);
arbre_t** RechercheHorizontale(arbre_t* cellule, char lettre);
arbre_t** RechercheVerticale(arbre_t* cellule, char lettre);
char Minuscule(char lettre);
char Majuscule(char lettre);
arbre_t* Inserer(arbre_t* racine, char* mot);
arbre_t* InsererMot(arbre_t** racine, char* mot);
int taillemot(char* mot);
char* copie(char* source, int i);

#endif