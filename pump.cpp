#include <thread>
#include <chrono>
#include <iostream>
#include <iomanip>

#include <QDebug>

#include "pump.h"

using namespace std;

Pump::Pump(const QString &name, uint8_t address, QObject *parent)
    : QObject(parent)
    , I2C(address)
    , name_(name)
    , address_(address)
    , actualFlow_(0)
    , desiredFlow_(0)
    , pumped_(0)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(100);
}

double Pump::actualFlow() const
{
    return actualFlow_;
}

void Pump::actualFlow(double f)
{
    if (f != actualFlow_) {
        actualFlow_ = f;
        emit(actualFlowChanged(f));
    }
}

double Pump::desiredFlow() const
{
    return desiredFlow_;
}

void Pump::setDesiredFlow(double f)
{
    qDebug() << __PRETTY_FUNCTION__ << f;
    if (f != desiredFlow_) {
        desiredFlow_ = f;
        emit desiredFlowChanged(desiredFlow_);
        actualFlow(f);
    }
}

void Pump::start()
{
    cout << __PRETTY_FUNCTION__;
    status.set(Running);
    emit runningChanged(running());
    uint16_t crap = read(0x0);
    cout << __PRETTY_FUNCTION__ << ": " << hex << crap << dec << endl;
    crap = read(0x1);
    cout << __PRETTY_FUNCTION__ << ": " << hex << crap << dec << endl;
    crap = read(0x2);
    cout << __PRETTY_FUNCTION__ << ": " << hex << crap << dec << endl;
    //thread t([this]() {
        //this_thread::sleep_for(chrono::seconds(5));
        //stop();
        //actualFlow(0);
    //});
    //t.detach();
}

void Pump::stop()
{
    qDebug() << __PRETTY_FUNCTION__;
    status.reset(Running);
    emit runningChanged(running());
}

void Pump::update()
{
    //qDebug() << __PRETTY_FUNCTION__;
}
