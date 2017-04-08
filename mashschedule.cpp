#include <QDebug>
#include "mashschedule.h"

Rest::Rest(QObject *parent)
    : QObject(parent)
    , name_("Rest")
    , temp_(150)
    , time_(30)
{

}
Rest::Rest(const QString &name, uint temp, uint time, QObject *parent)
    : QObject(parent)
    , name_(name)
    , temp_(temp)
    , time_(time)
{
    qDebug() << *this;
}

MashSchedule::MashSchedule(QObject *parent)
    : QAbstractListModel(parent)
{

}

int MashSchedule::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    qDebug() << __PRETTY_FUNCTION__ << ": enter ";
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
        return rests[index.row()]->time();
    }
    return QVariant();
}

void MashSchedule::append(int row, const QString &name, uint temp, uint time)
{
    qDebug() << __PRETTY_FUNCTION__ << ": enter" << row << " " << name << " " << temp << " " << time;
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
}

void MashSchedule::set(int row, const QString &name, uint temp, uint time)
{
    qDebug() << __PRETTY_FUNCTION__ << ": enter" << row << " " << name << " " << temp << " " << time;
    if (row < 0 || rests.size() <= row) {
        return;
    }
    rests[row].reset(new Rest(name, temp, time, this));
    dataChanged(index(row, 0), index(row, 0));
}

void MashSchedule::remove(int row)
{
    qDebug() << __PRETTY_FUNCTION__ << ": enter" << row;
    if (row < 0 || rests.size() <= row) {
        return;
    }
    beginRemoveColumns(QModelIndex(), row, row);
    rests.erase(rests.begin() + row);
    endRemoveRows();
}

Rest* MashSchedule::get(int row)
{
    qDebug() << __PRETTY_FUNCTION__ << ": enter" << row;
    if (rests.size() <= row) {
        return NULL;
    }
    qDebug() << __PRETTY_FUNCTION__ << ": good fucking index " << rests.at(row).get()->name();
    return rests.at(row).get();
}

QHash<int, QByteArray> MashSchedule::roleNames() const
{
    qDebug() << __PRETTY_FUNCTION__ << ": enter";
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[TempRole] = "temp";
    roles[TimeRole] = "time";
    return roles;
}
