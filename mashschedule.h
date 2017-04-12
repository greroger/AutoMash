#pragma once

#include <string>
#include <vector>
#include <QAbstractListModel>
#include <QObject>
#include <QString>
#include <QDebug>

#include "helpers.h"

class Rest : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString name READ name WRITE name NOTIFY nameChanged)
    Q_PROPERTY(double temp READ temp WRITE temp NOTIFY tempChanged)
    Q_PROPERTY(QString time READ timeQString WRITE time NOTIFY timeChanged)
    typedef std::shared_ptr<Rest> Ptr;

public:
    explicit Rest(QObject *parent = 0);
    Rest(const QString &name, int temp, const time_duration &time, QObject *parent = 0);
    Rest(const QString &name, int temp, const QString &time, QObject *parent = 0);
    static Ptr create(const QString &name, int temp, const time_duration &time, QObject *parent = 0);
    virtual ~Rest() {}

    const QString& name() const { return name_; }
    void name(const QString &n) { if (n != name_) { name_ = n; emit nameChanged(name_); } }
    double temp() const { return temp_; }
    void temp(double t) { if (t != temp_) { temp_ = t; emit tempChanged(temp_); } }
    QString timeQString() const { return toQString(time_); }
    const time_duration& time() const { return time_; }
    void time(const QString &t);
signals:
    void nameChanged(QString);
    void tempChanged(double);
    void timeChanged(QString);
private:
    QString name_;
    double temp_;
    time_duration time_;
};

class MashSchedule : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString totalTime READ totalTime NOTIFY totalTimeChanged)
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        TempRole,
        TimeRole
    };
    Q_ENUM(Roles);

    MashSchedule(QObject *parent = 0);
    virtual ~MashSchedule() {}

    void addRest(const Rest::Ptr &r) { rests.push_back(r); recalc(); }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE void append(int row, const QString &name, double temp, const QString &time);
    Q_INVOKABLE void set(int row, const QString &name, double temp, const QString &time);
    Q_INVOKABLE void remove(int row);
    Q_INVOKABLE Rest* get(int row);

    QString totalTime() const { return toQString(totalTime_); }
signals:
    void countChanged(int);
    void totalTimeChanged(QString);
protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    void recalc();
    std::vector<Rest::Ptr> rests;
    time_duration totalTime_;
};
