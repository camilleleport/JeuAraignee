#ifndef JOUEUR_H
#define JOUEUR_H

#include <iostream>
using namespace std;

#include "pion.h"

class Joueur
{
public:
    Joueur(string name);
    ~Joueur();
    Joueur(const Joueur& J1);

    string getNom();
    void setNom(string nom);
    void placePion(int z);
    bool victoire();
    Pion* selectionnePion(int n);


private:
    string nom;
    int ind;
    Pion* Jeu[3];
};

#endif // JOUEUR_H
