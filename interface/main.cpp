#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


#include <QCoreApplication>
#include <QQmlEngine>
#include <QQmlComponent>

#include "network.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);


    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Network network;
    Settings settings;

    Servers serv;
    network._serverlist= &serv;

    settings.setClient(&network);

    QList<QObject*> cardlist;
    cardlist.append(new QObject());
    cardlist.at(0)->setProperty("path","dqzfghtf");

    QQmlContext *ctx=engine.rootContext();

    ctx->setContextProperty("network", &network);
    ctx->setContextProperty("settings", &settings);

    ctx->setContextProperty("cardListModel", QVariant::fromValue(cardlist));
    qmlRegisterType<Servers>();
    ctx->setContextProperty("serverListModel", &serv);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    settings.loadSettings();

    qDebug() << "Serv count: " <<serv._serverlist.count();
    return app.exec();
}
