#include <QMetaType>
#include <QQmlContext>
#include <QGuiApplication>

#include "automash.h"

AutoMash::AutoMash(QObject *parent)
    : QObject(parent)
    , hltPump("HLT Pump", 0x14)
    , mashPump("Mash Pump", 0x6a)
{
    qmlRegisterType<Rest>("automash", 1, 0, "Rest");
    qmlRegisterType<Grain>("automash", 1, 0, "Grain");
    qmlRegisterType<Hop>("automash", 1, 0, "Hop");

    mashSchedule.add(Rest::create("Mash", 152, minutes(60)));
    mashSchedule.add(Rest::create("Mash Out", 170, minutes(10)));

    grainBill.add(Grain::create("British pale ale malt", 6.4));
    grainBill.add(Grain::create("British crystal malt", 0.3125));
    grainBill.add(Grain::create("Flaked maize", 0.3125));
    grainBill.add(Grain::create("Flaked barley", 0.3125));

    hops.add(Hop::create("Target", 1, minutes(75)));
    hops.add(Hop::create("Progress", 1, minutes(5)));

    qApp->setQuitOnLastWindowClosed(true);

    engine.rootContext()->setContextProperty("mashSchedule", &mashSchedule);
    engine.rootContext()->setContextProperty("grainBill", &grainBill);
    engine.rootContext()->setContextProperty("hops", &hops);
    engine.rootContext()->setContextProperty("hops", &hops);
    engine.rootContext()->setContextProperty("hltPump", &hltPump);
    engine.rootContext()->setContextProperty("mashPump", &mashPump);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
}
