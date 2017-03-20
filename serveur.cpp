#include "serveur.h"

Serveur::Serveur()
{
    for(int i=0; i<9; i++){
        Occupation[i]=0;
    }
    tour=1;
    phase=0;
    JoueurQuiALaMain=1;
}
