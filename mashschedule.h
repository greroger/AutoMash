#ifndef MASHSCHEDULE_H
#define MASHSCHEDULE_H

#include <vector>
#include <QAbstractListModel>
#include <QObject>
#include <QString>

class Rest : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString name READ name WRITE name NOTIFY nameChanged)
    Q_PROPERTY(int temp READ temp WRITE temp NOTIFY tempChanged)
    Q_PROPERTY(int time READ time WRITE time NOTIFY timeChanged)
    typedef std::shared_ptr<Rest> Ptr;

public:
    explicit Rest(QObject *parent = 0);
    Rest(const QString &name, uint temp, uint time, QObject *parent = 0);
    virtual ~Rest() {}

    const QString& name() const { return name_; }
    void name(const QString &n) { if (n != name_) { name_ = n; emit nameChanged(name_); } }
    int temp() const { return temp_; }
    void temp(int t) { if (t != temp_) { temp_ = t; emit tempChanged(temp_); } }
    int time() const { return time_; }
    void time(int t) { if (t != time_) { time_ = t; emit timeChanged(time_); } }
    operator QString() const
    {
        return name_ + ", " + QString().setNum(temp_) + ", " + QString().setNum(time_);
    }
signals:
    void nameChanged(QString);
    void tempChanged(int);
    void timeChanged(int);
private:
    QString name_;
    int temp_;
    int time_;
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
    Q_ENUM(Roles);

    MashSchedule(QObject *parent = 0);
    virtual ~MashSchedule() {}
    //void addRest(const Rest &r) { rests.push_back(r); }
    Qt::ItemFlags flags(const QModelIndex &) const override { return Qt::ItemIsEditable; }
    int rowCount(const QModelIndex &/*parent*/ = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE void append(int row, const QString &name, uint temp, uint time);
    Q_INVOKABLE void set(int row, const QString &name, uint temp, uint time);
    Q_INVOKABLE void remove(int row);
    Q_INVOKABLE Rest* get(int row);
signals:
    void countChanged(int);
protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    std::vector<Rest::Ptr> rests;
};

#endif // MASHSCHEDULE_H
