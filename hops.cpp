#include "hops.h"

Hop::Hop(QString name, double amount, time_duration time, QObject *parent)
    : QObject(parent)
    , name_(name)
    , amount_(amount)
    , time_(time)
{
}

Hop::Hop(QString name, double amount, QString time, QObject *parent)
    : QObject(parent)
    , name_(name)
    , amount_(amount)
    , time_(minutes(time.toLong()))
{
}

Hop::Ptr Hop::create(QString name, double amount, time_duration time, QObject *parent)
{
    return Ptr(new Hop(name, amount, time, parent));
}

Hop::Ptr Hop::create(QString name, double amount, QString time, QObject *parent)
{
    return Ptr(new Hop(name, amount, time, parent));
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

void Hops::add(const Hop::Ptr &p)
{
    beginResetModel();
    hops.push_back(p);
    sort();
    endResetModel();
    recalc();
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

void Hops::append(int row, const QString &name, double amount, QString time)
{
    beginResetModel();
    hops.push_back(Hop::create(name, amount, time, this));
    sort();
    endResetModel();
    recalc();
}

void Hops::set(int row, const QString &name, double amount, QString time)
{
    if (row < 0 || hops.size() <= row) {
        return;
    }
    beginResetModel();
    hops[row].reset(new Hop(name, amount, time, this));
    sort();
    endResetModel();
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
    sort();
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
