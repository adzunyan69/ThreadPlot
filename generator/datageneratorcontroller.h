#ifndef DATAGENERATORCONTROLLER_H
#define DATAGENERATORCONTROLLER_H

#include <QObject>
#include <QThread>
#include "datagenerator.h"

class DataGeneratorController : public QObject
{
    Q_OBJECT
public:
    explicit DataGeneratorController(QObject *parent = nullptr);
    ~DataGeneratorController();
private:
    QThread *thread{ nullptr };

public slots:
    void start();
    void suspend();
    void resume();
    void stop();

private slots:
    void data(double x, double y);

signals:
    void suspended();
    void resumed();

    void dataReceived(double x, double y);
};

#endif // DATAGENERATORCONTROLLER_H
