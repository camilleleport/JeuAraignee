#ifndef PION_H
#define PION_H

#include <iostream>
using namespace std;

class Pion
{
public:
    Pion(int n);

    int getLigne();
    int getColonne();
    int getNumero();

    void setLigne(int ligne);
    void setColonne(int colonne);
    void setNumero(int numero);

    bool estVoisin(int n);

private:
    int ligne;
    int colonne;
    int numero;
};

#endif // PION_H
