#include <sstream>
#include <QDebug>
#include "mashschedule.h"

Rest::Rest(QObject *parent)
    : QObject(parent)
    , name_("Rest")
    , temp_(150)
    , time_(minutes(30))
{

}
Rest::Rest(const QString &name, int temp, const time_duration &time, QObject *parent)
    : QObject(parent)
    , name_(name)
    , temp_(temp)
    , time_(time)
{
}

Rest::Rest(const QString &name, int temp, const QString &time, QObject *parent)
    : QObject(parent)
    , name_(name)
    , temp_(temp)
    , time_(minutes(time.toLong()))
{
}

Rest::Ptr Rest::create(const QString &name, int temp, const time_duration &time, QObject *parent)
{
    Ptr p(new Rest(name, temp, time, parent));
    return p;
}

void Rest::time(const QString &t)
{
    time_duration temp = minutes(t.toLong());
    if (temp != time_) {
        time_ = temp;
        emit(timeChanged(toQString(time_)));
    }
}

MashSchedule::MashSchedule(QObject *parent)
    : QAbstractListModel(parent)
{

}

int MashSchedule::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return rests.size();
}

QVariant MashSchedule::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case NameRole:
        return rests[index.row()]->name();
    case TempRole:
        return rests[index.row()]->temp();
    case TimeRole:
        return rests[index.row()]->timeQString();
    }
    return QVariant();
}

void MashSchedule::append(int row, const QString &name, double temp, const QString &time)
{
    if (row < 0 || rests.size() <= row) {
        beginInsertRows(QModelIndex(), rests.size(), rests.size());
        rests.push_back(Rest::Ptr(new Rest(name, temp, time, this)));
        endInsertRows();
    } else {
        ++row;
        beginInsertRows(QModelIndex(), row, row);
        rests.insert(rests.begin() + row, Rest::Ptr(new Rest(name, temp, time, this)));
        endInsertRows();
    }
    recalc();
}

void MashSchedule::set(int row, const QString &name, double temp, const QString &time)
{
    if (row < 0 || rests.size() <= row) {
        return;
    }
    rests[row].reset(new Rest(name, temp, time, this));
    dataChanged(index(row, 0), index(row, 0));
    recalc();
}

void MashSchedule::remove(int row)
{
    if (row < 0 || rests.size() <= row) {
        return;
    }
    beginRemoveColumns(QModelIndex(), row, row);
    rests.erase(rests.begin() + row);
    endRemoveRows();
    recalc();
}

Rest* MashSchedule::get(int row)
{
    if (rests.size() <= row) {
        return NULL;
    }
    return rests.at(row).get();
}

QHash<int, QByteArray> MashSchedule::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[TempRole] = "temp";
    roles[TimeRole] = "time";
    return roles;
}

void MashSchedule::recalc()
{
    int prev_temp = 0;
    totalTime_ = minutes(0);
    for (auto &&r: rests) {
        if (prev_temp != 0) {
            auto step = minutes((r->temp() - prev_temp) / 2);
            totalTime_ = totalTime_ + step;
        }
        totalTime_ += r->time();
        prev_temp = r->temp();
    }
    emit totalTimeChanged(toQString(totalTime_));
}
