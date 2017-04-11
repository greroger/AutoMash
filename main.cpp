#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include <QMetaType>

#include "mashschedule.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    qmlRegisterType<Rest>("automash", 1, 0, "Rest");

    MashSchedule mashSchedule;
    mashSchedule.addRest(Rest::create("Alpha-amylase", 158, minutes(60)));
    mashSchedule.addRest(Rest::create("Mash Out", 168, minutes(10)));

    qApp->setQuitOnLastWindowClosed(true);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("mashModel", &mashSchedule);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
