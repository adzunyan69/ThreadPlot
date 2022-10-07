#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      plotWidget(new PlotWidget(this)),
      start(new QPushButton(this)),
      pause(new QPushButton(this)),
      stop(new QPushButton(this))
{
    ui->setupUi(this);

    if ( initGUI()  == false )
        return;

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::initGUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLayout *buttonsLayout = new QHBoxLayout(this);

    if (
            mainLayout &&
            buttonsLayout &&
            plotWidget &&
            start &&
            pause &&
            stop )
    {
        centralWidget()->setLayout(mainLayout);
        mainLayout->addWidget(plotWidget);
        buttonsLayout->addWidget(start);
        buttonsLayout->addWidget(pause);
        buttonsLayout->addWidget(stop);
        mainLayout->addLayout(buttonsLayout);

        bool isConnected =
                connect(start, &QPushButton::clicked,
                        this, &MainWindow::startClicked) &&
                connect(pause, &QPushButton::clicked,
                        this, &MainWindow::pauseClicked) &&
                connect(stop, &QPushButton::clicked,
                        this, &MainWindow::stopClicked);

        if (isConnected)
            return true;
        else
            return false;
    }

    return false;
}

void MainWindow::testAppendData()
{
    qDebug() << "Test Appending Data to the Plot";

    static double lastX = 0.0;
    static double lastY = 0.0;

    if (plotWidget)
    {
        plotWidget->appendData(lastX, lastY);
        lastX += 0.5;
        lastY += 0.75;
    }
}

void MainWindow::startClicked()
{
    if (testTimer == nullptr)
    {
        testTimer = new QTimer(this);
        testTimer->setInterval(500);
        connect(testTimer, &QTimer::timeout,
            this, &MainWindow::testAppendData);
    }

    if (testTimer)
        testTimer->start();
}

void MainWindow::pauseClicked()
{
    if (testTimer)
        testTimer->stop();
}

void MainWindow::stopClicked()
{
    if (testTimer)
        testTimer->stop();

    if (plotWidget)
        plotWidget->clearData();
}
