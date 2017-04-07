#include <QDebug>
#include "mashschedule.h"

Rest::Rest()
    : QObject()
    , name_("Rest")
    , temp_(150)
    , time_(30)
{

}
Rest::Rest(const QString &name, uint temp, uint time)
    : name_(name), temp_(temp), time_(time)
{
    qDebug() << *this;
}

MashSchedule::MashSchedule(QObject *parent)
    : parent(parent)
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
        return rests[index.row()].name();
    case TempRole:
        return rests[index.row()].temp();
    case TimeRole:
        return rests[index.row()].time();
    }
    return QVariant();
}

void MashSchedule::addRow(const QModelIndex &index)
{
    qDebug() << __PRETTY_FUNCTION__ << ": enter " << index;
    if (index.isValid()) {
        beginInsertRows(index.parent(), index.row() + 1, index.row() + 1);
        rests.insert(index.row() + 1, Rest());
        endInsertRows();
    } else {
        beginInsertRows(index.parent(), rests.size(), rests.size());
        rests.push_back(Rest());
        endInsertRows();
    }
}

void MashSchedule::removeRow(const QModelIndex &index)
{
    qDebug() << __PRETTY_FUNCTION__ << ": enter " << index;
    if (index.isValid()) {
        beginRemoveRows(index.parent(), index.row(), index.row());
        rests.removeAt(index.row());
        endRemoveRows();
    }
}

bool MashSchedule::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << __PRETTY_FUNCTION__ << ": enter " << index << " " << value << " " << role;
    //emit dataChanged()
    return true;
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
