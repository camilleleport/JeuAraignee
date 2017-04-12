#include "joueur.h"


Joueur::Joueur (string name){
    nom=name; //nom du joueur


    // Le pb c'est qu'il ne sait pas comment construire un tableau de pions... Il comprend pas ce que c'est
    //C'est bon !

    ind=0; //Cet entier n'est utile que pour placer les 3 premiers pions dans la liste.
    Jeu[0]=new Pion(0); // il faut initialiser le tableau avec des pions sinon ça marche pas
    Jeu[1]=new Pion(0);
    Jeu[2]=new Pion(0);
}

/*
Joueur::~Joueur(){
    if (nom != NULL) {
        delete [] nom;
        delete [] ind;
        delete [] Jeu;
        nom=NULL;
        ind=NULL;
        Jeu=NULL;
    }
}*/

string Joueur::getNom() {
    return nom;
}

void Joueur::setNom(string name) {
    nom=name;
}

void Joueur::placePion(int z){ //Le joueur place un nouveau pion sur le jeu
    if (ind<=2){
        Jeu[ind]->setNumero(z); //On crée alors ce pion
        ind++;
    }
}

bool  Joueur::victoire(){
    //Cette fonction renvoie le boolean true lorsque les trois pion du joueur sont alignés
    bool victoire=false;
    if (Jeu[1]->getColonne()==Jeu[2]->getColonne() && Jeu[1]->getColonne()==Jeu[0]->getColonne())
        victoire=true; //Suivant une colonne
    if (Jeu[1]->getLigne()==Jeu[2]->getLigne() && Jeu[1]->getLigne()==Jeu[0]->getLigne())
        victoire=true; //Suivant une ligne
    if (Jeu[1]->getLigne()==Jeu[1]->getColonne() && Jeu[2]->getLigne()==Jeu[2]->getColonne() && Jeu[0]->getLigne()==Jeu[0]->getColonne())
        victoire=true; //Suivant la première diagonale
    if (Jeu[1]->getLigne()+Jeu[1]->getColonne()==2 && Jeu[2]->getLigne()+Jeu[2]->getColonne()==2 && Jeu[0]->getLigne()+Jeu[0]->getColonne()==2)
        victoire=true; //ou la seconde diagonale
    return victoire;
}

Pion Joueur::selectionnePion(int n){
    //Le joueur sélectionne un pion qui lui appartient.
    //Traitement est programmé pour que la fonction ne renvoie pas null
    Pion pionSelect=NULL;
    for (int i = 0; i<int(sizeof(Jeu)); i++ ) {
        int p=Jeu[i]->getNumero();
        if (n==p){
            pionSelect=p;
        }
    }
    return pionSelect;
}
