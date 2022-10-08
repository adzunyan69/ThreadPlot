#include "datageneratorcontroller.h"

DataGeneratorController::DataGeneratorController(QObject *parent)
    : QObject{parent}
{

}

DataGeneratorController::~DataGeneratorController()
{
    if (thread)
    {
        thread->quit();
        thread->wait();
    }
}

void DataGeneratorController::start()
{
    thread = new QThread;
    DataGenerator *dataGenerator = new DataGenerator();
    dataGenerator->moveToThread(thread);

    connect(thread, &QThread::started,
            dataGenerator, &DataGenerator::run);
    connect(thread, &QThread::finished,
            dataGenerator, &DataGenerator::deleteLater);
    connect(thread, &QThread::finished,
            thread, &QThread::deleteLater);
    connect(dataGenerator, &DataGenerator::dataGenerated,
            this, &DataGeneratorController::data, Qt::QueuedConnection);
    connect(this, &DataGeneratorController::suspended,
            dataGenerator, &DataGenerator::suspend, Qt::QueuedConnection);
    connect(this, &DataGeneratorController::resumed,
            dataGenerator, &DataGenerator::resume, Qt::QueuedConnection);

    thread->start();
}

void DataGeneratorController::suspend()
{
    emit suspended();
}


void DataGeneratorController::resume()
{
    emit resumed();
}

void DataGeneratorController::stop()
{
    if (thread)
    {
        thread->quit();
        thread->wait();
    }
}

void DataGeneratorController::data(double x, double y)
{
    dataReceived(x ,y);
}
