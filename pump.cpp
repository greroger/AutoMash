#include <thread>
#include <chrono>

#include <QDebug>

#include "pump.h"

Pump::Pump(const QString &name, uint8_t address, QObject *parent)
    : QObject(parent)
    , name_(name)
    , address_(address)
    , actualFlow_(0)
    , desiredFlow_(0)
{
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
    status.set(Running);
    emit runningChanged(running());
    std::thread t([this]() {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        stop();
        actualFlow(0);
    });
    t.detach();
}

void Pump::stop()
{
    qDebug() << __PRETTY_FUNCTION__;
    status.reset(Running);
    emit runningChanged(running());
}
