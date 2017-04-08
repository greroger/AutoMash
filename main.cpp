#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include "mashschedule.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    qDebug() << qmlRegisterType<Rest>("automash", 1, 0, "Rest") << "\n";

    MashSchedule mashSchedule;
    //mashSchedule.addRest(Rest("Alpha-amylase", 158, 60));
    //mashSchedule.addRest(Rest("Mash Out", 168, 10));

    qApp->setQuitOnLastWindowClosed(true);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("mashModel", &mashSchedule);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
