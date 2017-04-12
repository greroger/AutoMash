#pragma once

#include <memory>
#include <QObject>
#include <QAbstractListModel>

#include "helpers.h"

class Hop : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE name NOTIFY nameChanged)
    Q_PROPERTY(double amount READ amount WRITE amount NOTIFY amountChanged)
    Q_PROPERTY(QString time READ timeQString WRITE time NOTIFY timeChanged)
public:
    typedef std::shared_ptr<Hop> Ptr;
    enum Type {
          Pellet
        , Plug
        , Whole
    };
    Q_ENUM(Type);
public:
    explicit Hop(QObject *parent = NULL) : QObject(parent), type_(Pellet), amount_(0) {}
    explicit Hop(QString name, double amount, time_duration time, QObject *parent = NULL);
    explicit Hop(QString name, double amount, QString time, QObject *parent = NULL);
    static Ptr create(QString name, double amount, time_duration time, QObject *parent = NULL);
    static Ptr create(QString name, double amount, QString time, QObject *parent = NULL);
    virtual ~Hop() {}

    const QString& name() const { return name_; }
    void name(const QString &n) { if (n != name_) { name_ = n; emit(nameChanged(name_)); } }

    const Type& type() const { return type_; }
    void type(const Type &t) { if (t != type_) { type_ = t; emit(typeChanged(type_)); } }

    double amount() const { return amount_; }
    void amount(const double p) { if (amount_ != p) { amount_ = p; emit(amountChanged(amount_)); } }

    QString timeQString() const { return toQString(time_); }
    const time_duration& time() const { return time_; }
    void time(const QString &t);
    QHash<int, QByteArray> typeNames() const;
signals:
    void nameChanged(QString);
    void typeChanged(Type);
    void amountChanged(double);
    void timeChanged(QString);
private:
    QString name_;
    Type type_;
    double amount_;
    time_duration time_;
};

class Hops : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString minimumBoil READ minimumBoil NOTIFY minimumBoilChanged)
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        TypeRole,
        TimeRole,
        AmountRole
    };
    Q_ENUM(Roles);
public:
    Hops(QObject *parent = NULL);
    virtual ~Hops() {}
    void add(const Hop::Ptr &p) { hops.push_back(p); emit(countChanged(hops.size())); recalc(); }
    int rowCount(const QModelIndex &) const override { return hops.size(); }
    QVariant data(const QModelIndex &index, int role) const;

    Q_INVOKABLE void append(int row, const QString &name, double amount, QString time);
    Q_INVOKABLE void set(int row, const QString &name, double amount, QString time);
    Q_INVOKABLE void remove(int row);
    Q_INVOKABLE Hop* get(int row);

    QString minimumBoil() const { return toQString(min_boil); }
signals:
    void countChanged(int);
    void minimumBoilChanged(QString);
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    void recalc();
    std::vector<Hop::Ptr> hops;
    time_duration min_boil;
};
