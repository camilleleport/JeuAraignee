#ifndef SERVEUR_H
#define SERVEUR_H

#include <iostream>
using namespace std;

#include <QObject>

#include "pion.h"
#include "joueur.h"

class Serveur: public QObject
{
    Q_OBJECT
public:
    Serveur();
    Q_INVOKABLE void jouerUnCoup(int zone);


    Q_PROPERTY(QList<QString> srvrQML READ readServeur NOTIFY srvrChanged)
    Q_PROPERTY(QString txtQML READ readTxt NOTIFY txtChanged)

    QList<QString> readServeur();
    QString readTxt();

signals:
    void srvrChanged();
    void txtChanged();

private :
    void placement(int zone);
    void selection(int zone);
    void deplacement(int zone);

    QList<QString> Occupation;
    int JoueurQuiALaMain;
    int tour;
    int phase;
    QString col0;
    QString col1;
    QString col2;
    QString col3;
    QString texte;
    string nom;
    Pion* PionSelect;
    Joueur* Joueurs[3]; // il fallait construire ça comme ça, c'est ça qui ne marchait pas
    //int Occupation[9];
    //list<Joueur> Joueurs;
};

#endif // SERVEUR_H
