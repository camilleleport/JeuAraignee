#include "serveur.h"

Serveur::Serveur()
{
    col0="#00000000";
    col1="#FF0000";
    col2="#00FF00";
    col3="#0000FF";
    for(int i=0; i<9; i++){
        Occupation<<col0;
    }
    tour=1;
    phase=0;
    JoueurQuiALaMain=1;

    PionSelect=new Pion(0); //Pion arbitraire.

    Joueurs[0]=new Joueur("Raymond Deubaze"); //Faux joueur pour ne pas avoir Joueurs[0] vide
    Joueurs[1]=new Joueur("Camille");
    Joueurs[2]=new Joueur("Romain");
    Joueurs[1]->selectionnePion(2); //Pion arbitraire

    texte=("Bienvenue dans le jeu de l'Araignee, " +Joueurs[JoueurQuiALaMain]->getNom()+" à toi de commencer").c_str();


}

Serveur::~Serveur()
{
    if (PionSelect != NULL) {
        delete [] PionSelect;
        PionSelect=NULL;

    }
    if (Joueurs !=NULL){
        for (int i=0; i<3; i++){

            delete [] Joueurs[i];
            Joueurs[i]=NULL;
        }
    }
}

Serveur::Serveur(const Serveur& S)
{
    col0=S.col0;
    col1=S.col1;
    col2=S.col2;
    col3=S.col3;
    for(int i=0; i<9; i++){
        Occupation<<S.Occupation[i];
    }
    tour=S.tour;
    phase=S.phase;
    JoueurQuiALaMain=S.JoueurQuiALaMain;
    PionSelect=S.PionSelect;
    Joueurs[1]=S.Joueurs[1];
    Joueurs[2]=S.Joueurs[2];
    texte=S.texte;

}

QList<QString> Serveur::readServeur()
{
    return QList<QString>(Occupation);
}

QString Serveur::readTxt()
{
    return QString(texte);
}


void Serveur::jouerUnCoup(int zone){
    //Cette fonction est appelé dès qu'un joueur clique sur la zone de jeu.
    //Elle a pour but d'enregistrer son coup

    if (phase==0){
        placement(zone);
    }
    else if (phase==1){
        selection(zone);
    }
    else if (phase==2){
        deplacement(zone);
    }
}

void Serveur::placement(int zone){
    //Phase de placement
    if (Occupation[zone]==col0){
        //Place libre
        Joueurs[JoueurQuiALaMain]->placePion(zone);
        if (JoueurQuiALaMain==1){
            Occupation[zone]=col1;
            srvrChanged();
        }
        if (JoueurQuiALaMain==2){
            Occupation[zone]=col2;
            srvrChanged();
        }
        if (tour==3){ //Victoire possible dès ce tour.
            if(Joueurs[JoueurQuiALaMain]->victoire()){
                phase=3;
                texte=("Victoire de "+Joueurs[JoueurQuiALaMain]->getNom()).c_str();
                txtChanged();
            }
            else { //Sinon, tour suivant
                if (JoueurQuiALaMain==1){
                    JoueurQuiALaMain=2;
                    texte=(Joueurs[JoueurQuiALaMain]->getNom()+", place un pion").c_str();
                    txtChanged();
                }
                else {
                    JoueurQuiALaMain=1;
                    tour++;
                    phase=1;
                    texte=(Joueurs[JoueurQuiALaMain]->getNom()+", selectionne un pion à déplacer").c_str();
                    txtChanged();
                }
            }
        }
        if (tour<=2){
            if (JoueurQuiALaMain==1){
                JoueurQuiALaMain=2;
                texte=(Joueurs[JoueurQuiALaMain]->getNom()+", place un pion").c_str();
                txtChanged();
            }
            else{
                JoueurQuiALaMain=1;
                tour++;
                texte=(Joueurs[JoueurQuiALaMain]->getNom()+", place un pion").c_str();
                txtChanged();
            }

        }
    }
}

void Serveur::selection(int zone){
    //Phase de sélection
    if ((JoueurQuiALaMain==1 && Occupation[zone]==col1) || (JoueurQuiALaMain==2 && Occupation[zone]==col2 ) ){
        //Il s'agit d'un pion du bon joueur
        PionSelect=Joueurs[JoueurQuiALaMain]->selectionnePion(zone);  //On récupère en mémoire ce pion
        Occupation[zone]=col3;
        srvrChanged();//La zone de jeu comporte un pion sélectionné
        phase=2;
        texte=(Joueurs[JoueurQuiALaMain]->getNom()+", déplace ce pion le long d'un segment").c_str();
        txtChanged();
    }
}

void Serveur::deplacement(int zone){

    //Cas où on déselectionne le pion.
    if (Occupation[zone]==col3){//On déselectionne le pion
        if (JoueurQuiALaMain==1){
            Occupation[zone]=col1;
            srvrChanged();
            texte=(Joueurs[JoueurQuiALaMain]->getNom()+", sélectionne un nouveau pion à déplacer.").c_str();
            txtChanged();
        }
        if (JoueurQuiALaMain==2){
            Occupation[zone]=2;
            srvrChanged();
            texte=(Joueurs[JoueurQuiALaMain]->getNom()+", sélectionne un nouveau pion à déplacer.").c_str();
            txtChanged();
        }
        phase=1;//On revient à la phase de sélection
    }

    //Cas où sélectionne une zone voisine, libre.
    else if (Occupation[zone]==col0 && PionSelect->estVoisin(zone)){
        Occupation[PionSelect->getNumero()]=col0;//On libère une case
        //srvrChanged();
        if (JoueurQuiALaMain==1){
            Occupation[zone]=col1;
            srvrChanged();
        }
        if (JoueurQuiALaMain==2){
            Occupation[zone]=col2;
            srvrChanged();
        }
        PionSelect->setNumero(zone);//On notifie que le pion du joueur change de zone
        if (Joueurs[JoueurQuiALaMain]->victoire()){//Cas de la victoire
            phase=3;
            texte=("Victoire de "+ Joueurs[JoueurQuiALaMain]->getNom()).c_str();
            txtChanged();
        }
        else{//Sinon on continue de jouer
            phase=1;
            if (JoueurQuiALaMain==1){
                JoueurQuiALaMain=2;
                texte=(Joueurs[JoueurQuiALaMain]->getNom()+", sélectionne un pion à déplacer.").c_str();
                txtChanged();
            }
            else{
                JoueurQuiALaMain=1;
                tour++;
                texte=(Joueurs[JoueurQuiALaMain]->getNom()+", sélectionne un pion à déplacer.").c_str();
                txtChanged();
            }
        }
    }
}
