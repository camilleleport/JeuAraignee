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

public int[] getOccupation() 
    return Occupation;
}

public void jouerUnCoup(int zone){
    //Cette fonction est appelé dès qu'un joueur clique sur la zone de jeu.
    //Elle apour but d'enregistrer son coup
        if (phase==0){ //Phase de placement
            if (Occupation[zone]==0){ //Case vide
                Occupation[zone]=JoueurQuiALaMain;   
            }
        }
}
