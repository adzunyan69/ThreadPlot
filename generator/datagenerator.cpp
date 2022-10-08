#include "datagenerator.h"

DataGenerator::DataGenerator(QObject *parent)
    : QObject{parent},
      timer(new QTimer(this))
{
    timer->setInterval(500);
}

DataGenerator::~DataGenerator()
{
    qInfo() << "Deleted";
}

void DataGenerator::run()
{
    QEventLoop eventLoop;

    qDebug() << "created event loop";

    auto generate = [this]
    {
        double x = QRandomGenerator::global()->generateDouble();
        double y = QRandomGenerator::global()->generateDouble();
        qInfo() << "generate: " << x << " " << y;
        emit dataGenerated(x, y);
    };

    connect(timer, &QTimer::timeout,
            &eventLoop, generate);

    timer->start();

    eventLoop.exec();
}

void DataGenerator::suspend()
{
    qInfo() << "suspend data generator";
    timer->stop();
}

void DataGenerator::resume()
{
    qInfo() << "resumed data generator";
    timer->start();
}
