#pragma once

#include <QObject>
#include <QQmlApplicationEngine>

#include "mashschedule.h"
#include "grainbill.h"
#include "hops.h"
#include "pump.h"

class AutoMash : public QObject
{
    Q_OBJECT
public:
    explicit AutoMash(QObject *parent = 0);

signals:

public slots:
private:
    MashSchedule mashSchedule;
    GrainBill grainBill;
    Hops hops;
    Pump hltPump;
    Pump mashPump;

    QQmlApplicationEngine engine;
};
