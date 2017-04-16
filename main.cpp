#include <iostream>
#include <thread>
#include <QGuiApplication>
#include <QtQml>

#include <automash.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Greg Rogers");
    QCoreApplication::setOrganizationDomain("gregoryrogers.me");
    QCoreApplication::setApplicationName("AutoMash");

    QSettings settings;

    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    AutoMash automash;

    return app.exec();
}
