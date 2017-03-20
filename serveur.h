#ifndef SERVEUR_H
#define SERVEUR_H

#include <iostream>
using namespace std;

class Serveur
{
public:
    Serveur();
    int[] getOccupation();
    void jouerUnCoup(int zone);
    
private :
    int Occupation[9];
    int JoueurQuiALaMain;
    int tour;
    int phase;


};

#endif // SERVEUR_H
