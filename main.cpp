#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include <QMetaType>

#include "mashschedule.h"
#include "grainbill.h"
#include "hops.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Greg Rogers");
    QCoreApplication::setOrganizationDomain("gregoryrogers.me");
    QCoreApplication::setApplicationName("AutoMash");

    QSettings settings;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<Rest>("automash", 1, 0, "Rest");
    qmlRegisterType<Grain>("automash", 1, 0, "Grain");
    qmlRegisterType<Hop>("automash", 1, 0, "Hop");

    MashSchedule mashSchedule;
    mashSchedule.add(Rest::create("Mash", 152, minutes(60)));
    mashSchedule.add(Rest::create("Mash Out", 170, minutes(10)));

    GrainBill grainBill;
    grainBill.add(Grain::create("British pale ale malt", 6.4));
    grainBill.add(Grain::create("British crystal malt", 0.3125));
    grainBill.add(Grain::create("Flaked maize", 0.3125));
    grainBill.add(Grain::create("Flaked barley", 0.3125));

    Hops hops;
    hops.add(Hop::create("Target", 1, minutes(75)));
    hops.add(Hop::create("Progress", 1, minutes(5)));

    qApp->setQuitOnLastWindowClosed(true);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("mashSchedule", &mashSchedule);
    engine.rootContext()->setContextProperty("grainBill", &grainBill);
    engine.rootContext()->setContextProperty("hops", &hops);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
