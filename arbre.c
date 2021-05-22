#include "arbre.h"
#include "pile.h"

pile_t* InitialiserPile()
{
    pile_t* tete = malloc(sizeof(pile_t));
    tete->value = NULL;
    tete->next = NULL;
    return tete;
}

void Empiler(pile_t** tete, arbre_t* val)
{
    pile_t* nv = malloc(sizeof(pile_t));
    if ((tete != NULL) || (nv != NULL))
    {
        nv->value = val;
        nv->next = *tete;
        (*tete) = nv;
    }
}

void Depiler(pile_t** tete)
{
    pile_t* tmp = (*tete);

    if (tete != NULL)
    {
        (*tete) = (*tete)->next;
    }

    //free(tmp);
}

void AfficherPile(pile_t* tete)
{
    pile_t* tmp = tete;
    while (tmp->value != NULL)
    {
        printf("%c", tmp->value->contenu);
        tmp = tmp->next;
    }
    printf("\n");
}

void AfficherPileInverse(pile_t* tete)
{
    pile_t* nv = InitialiserPile();
    pile_t* tmp = tete;
    if (nv != NULL)
    {
        while (tmp->value != NULL)
        {
            Empiler(&nv, tmp->value);
            tmp = tmp->next;
        }
        AfficherPile(nv);
    }
}

bool estVide(pile_t* tete)
{
    bool resultat = false;
    if (tete == NULL) resultat = true;
    return resultat;
}

int main()
{
    /*arbre_t a1, a2, a3;
    a1.contenu = 'a';
    a2.contenu = 'b';
    a3.contenu = 'c';
    
    a1.lv = &a2;
    a1.lh = NULL;
    a2.lv = NULL;
    a2.lh = &a3;
    a3.lv = NULL;
    a3.lh = NULL;

    printf("%c\n", a1.contenu);
    printf("|\n");
    printf("%c\n", a2.lh->contenu);*/

    //char not[] = "(a*(b*(a*T+i*m*E)+r*(d*U+T*S))+d*a*b*a*b*Y)";
    //char not[] = "(a*b*c+b)";
    char* ex;

    arbre_t* arbre = NULL;

    //arbre = NotAlgEnArbre(not);

    arbre = Inserer(arbre, "dragon");

    arbre = Inserer(arbre, "achraf");

    //AfficherDictionnaire(arbre);

    //printf("%d\n",taillemot("mot"));

    //ex = copie("poopie", 2);

    //printf("%s\n", ex);

    if (RechercheHorizontale(arbre, 'a') == NULL) printf("NULL !\n");

    return 0;
}

arbre_t* NotAlgEnArbre(char* notation)
{
    arbre_t* arbre = NULL;
    pile_t* ptr_pile = InitialiserPile();
    arbre_t** prec = &arbre;
    int code = 0;
    int i = 0;

    while (notation[i] != '\0')
    {
        switch(notation[i])
        {
            case '*' :
                if (code == 0) Empiler(&ptr_pile, *prec);
                prec = &((*prec)->lv);
                code++;
                i++;
                break;
            case '+' :
                prec = &(ptr_pile->value->lh);
                Depiler(&ptr_pile);
                code = 0;
                i++;
                break;
            case ')' :
                Depiler(&ptr_pile);
                code = 0;
                i++;
                break;
            case '(' :
                code = 0;
                i++;
                break;
            default :
                *prec = Ajouter(prec, notation[i]);
                if ((notation[i+1] == '+') && (code == 0)) Empiler(&ptr_pile, *prec);
                i++;
                break;
        }
    }
    free(ptr_pile);
    return arbre;
}

arbre_t* Ajouter(arbre_t** arbre, char a_ajouter)
{
    arbre_t* tmp = malloc(sizeof(arbre_t));
    if (tmp != NULL)
    {
        tmp->contenu = a_ajouter;
        tmp->lh = NULL;
        tmp->lv = NULL;
    }
    return tmp;
}

void AfficherDictionnaire(arbre_t* arbre)
{
    pile_t* ptr_pile = InitialiserPile();
    bool code = true;
    int verification = 0;
    arbre_t** prec = &arbre;

    while (code == true)
    {
        while (*prec != NULL)
        {
            Empiler(&ptr_pile, *prec);
            if (((*prec)->contenu >= 'A') && ((*prec)->contenu <= 'Z')) AfficherPileInverse(ptr_pile);
            prec = &((*prec)->lv);
        }
        prec = &(ptr_pile->value);
        while ((ptr_pile->value != NULL) && ((*prec)->lh == NULL))
        {
            Depiler(&ptr_pile);
            prec = &(ptr_pile->value);
        }
        if (ptr_pile->value == NULL) code = false;
        else
        {
            prec = &(ptr_pile->value->lh);
            Depiler(&ptr_pile);
        }
    }
}

arbre_t** RechercheHorizontale(arbre_t* cellule, char lettre)
{
    arbre_t* prec = cellule;
    arbre_t** cour = &cellule;

    if (prec != NULL)
    {
        while ((Minuscule(prec->contenu) < lettre) && (prec->lh != NULL))
        {
            prec = prec->lh;
        }
        if (Minuscule(prec->contenu) >= lettre) *cour = prec;
        /*if ((prec == NULL) || (Miniscule(prec->contenu) != lettre))
        {
            cour = &cellule;
            while ((*cour)->lh != prec)
            {
                cour = &((*cour)->lh);
            }
        }
        else cour = &prec;*/
    }
    else cour = NULL;
    return cour;
}

arbre_t** RechercheVerticale(arbre_t* cellule, char lettre)
{
    arbre_t* prec = cellule;
    arbre_t** cour = &cellule;

    while ((prec != NULL) && (Minuscule(prec->contenu) < lettre))
    {
        prec = prec->lv;
    }
    if ((prec == NULL) || (Minuscule(prec->contenu) != lettre))
    {
        while ((*cour)->lv != prec)
        {
            cour = &((*cour)->lv);
        }
        cour = &((*cour)->lv);
    }
    else cour = NULL;

    return cour;
}

char Minuscule(char lettre)
{
    char resultat = lettre;
    if ((lettre >= 65) && (lettre <= 90)) resultat = lettre + 32;
    return resultat;
}

char Majuscule(char lettre)
{
    char resultat = lettre;
    if (lettre == Minuscule(lettre)) resultat = lettre - 32;
    return resultat;
}

arbre_t* Inserer(arbre_t* racine, char* mot)
{
    int i = 0;
    arbre_t** prec = NULL;
    arbre_t** cour = &racine;
    arbre_t* tmp = NULL;
    char lettre;
    char* cp;
    //arbre_t*** pprec;
    bool code = true;
    while ((mot[i] != '\0') && (*cour != NULL) && (code == true))
    {
            /*if (*cour == NULL)
            {
                if (mot[i+1] == '\0') (*cour) = Ajouter(cour, Majuscule(mot[i]));
                else *cour = Ajouter(cour, mot[i]);
            }
            else
            {
                if (mot[i+1] == '\0') (*cour)->lv = Ajouter(cour, Majuscule(mot[i]));
                else (*cour)->lv = Ajouter(cour, mot[i]);
            }*/
        /*if (code == false)
        {
            if (mot[i+1] == '\0') (*cour) = Ajouter(cour, Majuscule(mot[i]));
            else *cour = Ajouter(cour, mot[i]);
            cour = &((*cour)->lv);
        }*/
        prec = RechercheHorizontale(*cour, mot[i]);
        lettre = (*prec)->contenu;
        //lettre = Minuscule(lettre);
        if (lettre > mot[i])
        {
            tmp = (*prec)->lv;
            (*prec)->lv = Ajouter(cour, mot[i]);
            (*prec)->lv->lh = tmp;
            i++;
            code = false;
        }
        if (lettre < mot[i])
        {
            cour = &((*prec)->lh);
            code = false;
        }
        else
        {
            cour = &((*prec)->lv);
            i++;
        }
    }
    cp = copie(mot, i);
    InsererMot(cour, cp);
    return racine;
}

arbre_t* InsererMot(arbre_t** racine, char* mot)
{
    int i = 0;
    arbre_t** prec = racine;
    while (mot[i] != '\0')
    {
        if (mot[i+1] == '\0') *prec = Ajouter(racine, Majuscule(mot[i]));
        else *prec = Ajouter(racine, mot[i]);
        prec = &((*prec)->lv);
        i++;
    }
    return *racine;
}

int taillemot(char* mot)
{
    int i = 0;
    while (mot[i] != '\0')
    {
        i++;
    }
    return i;
}

char* copie(char* source, int i)
{
    int taille = taillemot(source) - i + 1;
    char* destination = malloc(taille*sizeof(char));
    for (int j=0;j<taille;j++)
    {
        destination[j] = source[i+j];
    }
    return destination;    
}