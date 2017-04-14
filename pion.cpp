#include "pion.h"

Pion::Pion(int n)
{
    //On repère un pion dans le jeu à partir de sa zone ou bien de sa ligne et de sa colonne.
    numero=n;
    colonne=n%3;
    ligne=(n-colonne)/3;
}


int Pion::getLigne() {
    return ligne;
}

int Pion::getColonne() {
    return colonne;
}

int Pion::getNumero() {
    return numero;
}

void Pion::setLigne(int l) {
    ligne = l;
    numero=3*ligne+colonne;
}

void Pion::setColonne(int c) {
    colonne = c;
    numero=3*ligne+colonne;
}

void Pion::setNumero(int n) {
    numero = n;
    colonne=numero%3;
    ligne=(numero-colonne)/3;
}

bool Pion::estVoisin(int n){
    //Cette fonction renvoie true lorsque le pion est voisin de la zone n du jeu, à savoir relié par un segment
    bool tmp;
    tmp=false;
    if ((numero-n==3) || (n-numero==3)) //segment vertical
        tmp=true;
    else if (((numero-n==1) && (numero%3!=0)) || ((n-numero==1)&&(n%3!=0))) //segment horizontal
        tmp=true;
    else if ((numero==4||n==4) && ((numero-n==2) || (n-numero==2) || (numero-n==4) || (n-numero==4))) //diagonalement
        tmp=true;
    return tmp;
}
