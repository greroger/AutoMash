#pragma once

#include <memory>
#include <QObject>
#include <QAbstractListModel>

class Grain : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE name NOTIFY nameChanged);
    Q_PROPERTY(double amount READ amount WRITE amount NOTIFY amountChanged);
public:
    typedef std::shared_ptr<Grain> Ptr;
public:
    Grain(QObject *parent = NULL) : QObject(parent) {}
    Grain(const QString &n, double p, QObject *parent = NULL) : QObject(parent), name_(n), amount_(p) {}
    static Ptr create(const QString &n, double p, QObject *parent = NULL) { return Ptr(new Grain(n, p, parent)); }

    const QString& name() const { return name_; }
    void name(const QString &n) { if (n != name_) { name_ = n; emit(nameChanged(name_)); } }

    double amount() const { return amount_; }
    void amount(const double p) { if (amount_ != p) { amount_ = p; emit(amountChanged(amount_)); } }
signals:
    void nameChanged(QString);
    void amountChanged(double);
private:
    QString name_;
    double amount_;
};

class GrainBill : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(double totalAmount READ totalAmount NOTIFY totalAmountChanged)
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        AmountRole
    };
    Q_ENUM(Roles);

    GrainBill(QObject *parent = 0);
    virtual ~GrainBill() {}

    void addGrain(const Grain::Ptr &r) { grains.push_back(r); recalc(); emit(countChanged(grains.size())); }

    int rowCount(const QModelIndex &) const override { return grains.size(); }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE void append(int row, const QString &name, double amount);
    Q_INVOKABLE void set(int row, const QString &name, double amount);
    Q_INVOKABLE void remove(int row);
    Q_INVOKABLE Grain* get(int row);

    double totalAmount() const { return totalAmount_; }
signals:
    void countChanged(int);
    void totalAmountChanged(double);
protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    void recalc();
    std::vector<Grain::Ptr> grains;
    double totalAmount_;
};
