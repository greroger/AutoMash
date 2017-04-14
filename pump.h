#pragma once

#include <atomic>

#include <QObject>
#include <QTimer>

#include "helpers.h"

class Pump : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)
    Q_PROPERTY(bool failed READ failed NOTIFY failedChanged)
    Q_PROPERTY(double actualFlow READ actualFlow NOTIFY actualFlowChanged)
    Q_PROPERTY(double desiredFlow READ desiredFlow WRITE setDesiredFlow NOTIFY desiredFlowChanged)
    Q_PROPERTY(double pumped READ pumped NOTIFY pumpedChanged)
public:
    enum Status_ {
        Running = 1 << 0,
        Failed = 1 << 1,
    };
    typedef Enumeration<Status_> Status;
public:
    Pump(const QString &name, uint8_t address, QObject *parent = NULL);

    const QString& name() const { return name_; }
    double actualFlow() const;
    void actualFlow(double f);

    bool running() const { return status.test(Running); }
    bool failed() const { return status.test(Failed); }

    double desiredFlow() const;
    void setDesiredFlow(double f);

    double pumped() const { return pumped_; }
signals:
    void nameChanged(QString);
    void runningChanged(bool running);
    void failedChanged(bool);
    void actualFlowChanged(double);
    void desiredFlowChanged(double);
    void pumpedChanged(double);

public slots:
    void start();
    void stop();
    void resetPumped() { pumped_ = 0; emit pumpedChanged(pumped_); }
    void update();

private:
    const QString name_;
    const uint8_t address_;
    std::atomic<uint8_t> actualFlow_;
    std::atomic<uint8_t> desiredFlow_;
    Status status;
    double pumped_;
    QTimer timer;
};

