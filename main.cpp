#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "serveur.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Serveur Plateau;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("vueObjetSrvr", &Plateau);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}


