#include "datagenerator.h"

DataGenerator::DataGenerator(QObject *parent)
    : QObject{parent},
      timer(new QTimer(this))
{
    timer->setInterval(500);
}

DataGenerator::~DataGenerator()
{
    qInfo() << "Data Genrator Deleted";
}

void DataGenerator::run()
{
    QEventLoop eventLoop;
    qInfo() << "Data Generator Started";

    auto generate = [this]
    {
        double x = QRandomGenerator::global()->generateDouble() * 100 - 50;
        double y = QRandomGenerator::global()->generateDouble() * 100 - 5;
        qInfo() << "Generated values (x, y): " << x << " " << y;
        emit dataGenerated(x, y);
    };

    connect(timer, &QTimer::timeout,
            &eventLoop, generate);

    timer->start();

    eventLoop.exec();
}

void DataGenerator::suspend()
{
    qInfo() << "Data Generator Suspended";
    timer->stop();
}

void DataGenerator::resume()
{
    qInfo() << "Data Generator Resumed";
    timer->start();
}
