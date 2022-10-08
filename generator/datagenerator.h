#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <QObject>
#include <QRandomGenerator>
#include <QTimer>
#include <QEventLoop>
#include <QDebug>
class DataGenerator : public QObject
{
    Q_OBJECT
public:
    explicit DataGenerator(QObject *parent = nullptr);
    ~DataGenerator();
private:
    QTimer *timer{ nullptr };

public slots:
    void run();
    void suspend();
    void resume();

signals:
    void dataGenerated(double x, double y);
};

#endif // DATAGENERATOR_H
