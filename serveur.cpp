#include "serveur.h"

Serveur::Serveur()
{
    col0="#00000000";
    col1="#FF0000";
    col2="#00FF00";
    col3="#0000FF";
    for(int i=0; i<9; i++){
        Occupation<<col0;
        //Occupation[i]=0;
    }
    tour=1;
    phase=0;
    JoueurQuiALaMain=1;
    PionSelect=new Pion(0); //Pion arbitraire.

    //Je garde volontairement Joueurs[0]=null pour éviter une confusion d'indice 0/1-1/2
    //Joueurs[0]=NULL;
    Joueurs[1]=new Joueur("Camille");
    Joueurs[2]=new Joueur("Romain");
    texte=("Bienvenue dans le jeu de l'Araignee, " +Joueurs[JoueurQuiALaMain]->getNom()+" à toi de commencer").c_str();


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
    //Elle apour but d'enregistrer son coup

    //texte=(/*"zone : "+to_string(zone)+ */ ", Occ : "+ Occupation[zone] ).c_str(); // on rentre dans cette boucle mais pas celle d'après
    txtChanged();

    if (phase==0){
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
            if (tour==3){
                if(Joueurs[JoueurQuiALaMain]->victoire()){
                    phase=3;
                    texte=("Victoire de "+Joueurs[JoueurQuiALaMain]->getNom()).c_str();
                    txtChanged();
                }
                else {
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
    if (phase==1){//Phase de sélection
        if ((JoueurQuiALaMain==1 && Occupation[zone]==col1) || (JoueurQuiALaMain==2 && Occupation[zone]==col2 ) ){
            //Il s'agit d'un pion du bon joueur


//Si on commente la ligne suivante, on peut sélectionner le pion (au moins il apparaît bleu), mais on ne peux pas aller plus loin.
//Si on la décommente, ça merde avant !
            //*PionSelect=Joueurs[JoueurQuiALaMain]->selectionnePion(zone);  //On récupère en mémoire ce pion
            Occupation[zone]=col3;
            srvrChanged();//La zone de jeu comporte un pion sélectionné
            phase=4;//Phase temporaire
            texte=(Joueurs[JoueurQuiALaMain]->getNom()+", déplace ce pion le long d'un segment").c_str();
            txtChanged();

        }
    }
    if (phase==2){//Phase de déplacement
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
        if (Occupation[zone]==col0 && PionSelect->estVoisin(zone)){
            Occupation[PionSelect->getNumero()]=col0;//On libère une case
            //srvrChanged();
            if (JoueurQuiALaMain==1){
                //Occupation[PionSelect->getNumero()]=col1;
                Occupation[zone]=col1;
                //Couleur[zone]=col1;
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
    if (phase==4){
        phase=2; //Permet de cliquer à nouveau pour déplacer le pion
        //Cette étape est nécéssaire pour éviter de sélectionner/déselectionner un pion en un même clic.
    }
}
