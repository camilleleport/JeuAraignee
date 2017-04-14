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
    ~Serveur();
    Serveur(const Serveur& S);
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
    Joueur* Joueurs[3];

};

#endif // SERVEUR_H
