#include "hops.h"

Hop::Hop(QString name, Type type, double amount, time_duration time, QObject *parent)
    : QObject(parent)
    , name_(name)
    , type_(type)
    , amount_(amount)
    , time_(time)
{
}

Hop::Hop(QString name, Type type, double amount, QString time, QObject *parent)
    : QObject(parent)
    , name_(name)
    , type_(type)
    , amount_(amount)
    , time_(minutes(time.toLong()))
{
}

Hop::Ptr Hop::create(QString name, Type type, double amount, time_duration time, QObject *parent)
{
    return Ptr(new Hop(name, type, amount, time, parent));
}

Hop::Ptr Hop::create(QString name, Type type, double amount, QString time, QObject *parent)
{
    return Ptr(new Hop(name, type, amount, time, parent));
}

void Hop::time(const QString &t)
{
    time_duration temp = minutes(t.toLong());
    if (temp != time_) {
        time_ = temp;
        emit(timeChanged(toQString(time_)));
    }
}

QHash<int, QByteArray> Hop::typeNames() const
{
    QHash<int, QByteArray> roles;
    roles[Pellet] = "Pellet";
    roles[Plug] = "Plug";
    roles[Whole] = "Whole";
    return roles;

}

Hops::Hops(QObject *parent)
    : QAbstractListModel(parent)
{

}

QVariant Hops::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case NameRole:
        return hops[index.row()]->name();
    case TypeRole:
        return hops[index.row()]->type();
    case TimeRole:
        return toQString(hops[index.row()]->time());
    case AmountRole:
        return hops[index.row()]->amount();
    }
    return QVariant();
}

void Hops::append(int row, const QString &name, Hop::Type type, double amount, QString time)
{
    if (row < 0 || hops.size() <= row) {
        beginInsertRows(QModelIndex(), hops.size(), hops.size());
        hops.push_back(Hop::create(name, type, amount, time, this));
        endInsertRows();
    } else {
        ++row;
        beginInsertRows(QModelIndex(), row, row);
        hops.insert(hops.begin() + row, Hop::create(name, type, amount, time, this));
        endInsertRows();
    }
    recalc();
}

void Hops::set(int row, const QString &name, Hop::Type type, double amount, QString time)
{
    if (row < 0 || hops.size() <= row) {
        return;
    }
    hops[row].reset(new Hop(name, type, amount, time, this));
    dataChanged(index(row, 0), index(row, 0));
    recalc();
}

void Hops::remove(int row)
{
    if (row < 0 || hops.size() <= row) {
        return;
    }
    beginRemoveColumns(QModelIndex(), row, row);
    hops.erase(hops.begin() + row);
    endRemoveRows();
    recalc();
}

Hop* Hops::get(int row)
{
    if (hops.size() <= row) {
        return NULL;
    }
    return hops.at(row).get();
}

QHash<int, QByteArray> Hops::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[TypeRole] = "type";
    roles[AmountRole] = "amount";
    roles[TimeRole] = "time";
    return roles;
}

void Hops::recalc()
{
    min_boil = minutes(0);
    for (auto &&h: hops) {
        min_boil = std::max(min_boil, h->time());
    }
    emit(minimumBoilChanged(toQString(min_boil)));
}
