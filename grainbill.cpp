#include <QDebug>
#include "grainbill.h"

GrainBill::GrainBill(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant GrainBill::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case NameRole:
        return grains[index.row()]->name();
    case AmountRole:
        return grains[index.row()]->amount();
    }
    return QVariant();
}

void GrainBill::append(int row, const QString &name, double amount)
{
    if (row < 0 || grains.size() <= row) {
        beginInsertRows(QModelIndex(), grains.size(), grains.size());
        grains.push_back(Grain::create(name, amount, this));
        endInsertRows();
    } else {
        ++row;
        beginInsertRows(QModelIndex(), row, row);
        grains.insert(grains.begin() + row, Grain::create(name, amount, this));
        endInsertRows();
    }
    recalc();
}

void GrainBill::set(int row, const QString &name, double amount)
{
    if (row < 0 || grains.size() <= row) {
        return;
    }
    qDebug() << __PRETTY_FUNCTION__ << ": " << name << ", " << amount;
    grains[row].reset(new Grain(name, amount, this));
    dataChanged(index(row, 0), index(row, 0));
    recalc();
}

void GrainBill::remove(int row)
{
    if (row < 0 || grains.size() <= row) {
        return;
    }
    beginRemoveColumns(QModelIndex(), row, row);
    grains.erase(grains.begin() + row);
    endRemoveRows();
    recalc();
}

Grain* GrainBill::get(int row)
{
    if (grains.size() <= row) {
        return NULL;
    }
    return grains.at(row).get();
}

QHash<int, QByteArray> GrainBill::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[AmountRole] = "amount";
    return roles;
}

void GrainBill::recalc()
{
    totalAmount_ = 0;
    for (auto &&g: grains) {
        totalAmount_ += g->amount();
    }
    emit(totalAmountChanged(totalAmount_));
}
