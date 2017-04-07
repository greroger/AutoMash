#ifndef MASHSCHEDULE_H
#define MASHSCHEDULE_H

#include <vector>
#include <QAbstractListModel>
#include <QObject>
#include <QString>

class Rest : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name_ READ name WRITE name NOTIFY nameChanged)
    Q_PROPERTY(uint temp_ READ temp WRITE temp NOTIFY tempChanged)
    Q_PROPERTY(uint time_ READ time WRITE time NOTIFY timeChanged)
public:
    typedef std::shared_ptr<Rest> Ptr;

public:
    Rest();
    Rest(const QString &name, uint temp, uint time);
    ~Rest() {}
    Rest(const Rest &rhs) : name_(rhs.name_), temp_(rhs.temp_), time_(rhs.time_) {}
    const Rest& operator=(const Rest &rhs) {
        name_ = rhs.name_;
        temp_ = rhs.temp_;
        time_ = rhs.time_;
        return *this;
    }

    const QString& name() const { return name_; }
    void name(const QString &n) { name_ = n; }
    uint temp() const { return temp_; }
    void temp(uint t) { temp_ = t; }
    uint time() const { return time_; }
    void time(uint t) { time_ = t; }
    operator QString() const
    {
        return name_ + ", " + QString().setNum(temp_) + ", " + QString().setNum(time_);
    }
signals:
    void nameChanged(QString);
    void tempChanged(uint);
    void timeChanged(uint);
private:
    QString name_;
    uint temp_;
    uint time_;
};

class MashSchedule : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        TempRole,
        TimeRole
    };

    MashSchedule(QObject *parent = 0);
    virtual ~MashSchedule() {}
    void addRest(const Rest &r) { rests.push_back(r); }
    Qt::ItemFlags flags(const QModelIndex &) const override { return Qt::ItemIsEditable; }
    int rowCount(const QModelIndex &/*parent*/ = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE void append(int row, const QString &name, uint temp, uint time);
    Q_INVOKABLE void set(int row, const QString &name, uint temp, uint time);
    Q_INVOKABLE void remove(int row);
signals:
    void countChanged(int);
protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<Rest> rests;
    QObject *parent;
};

#endif // MASHSCHEDULE_H
