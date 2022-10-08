#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      plotWidget(new PlotWidget(this)),
      dataGeneratorController(new DataGeneratorController(this)),
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

        setButtonIcon(start, ":/icons/start");
        setButtonIcon(pause, ":/icons/pause");
        setButtonIcon(stop, ":/icons/stop");

        pause->setEnabled(false);
        stop->setEnabled(false);

        bool isConnected =
                connect(start, &QPushButton::clicked,
                        this, &MainWindow::startClicked) &&
                connect(pause, &QPushButton::clicked,
                        this, &MainWindow::pauseClicked) &&
                connect(stop, &QPushButton::clicked,
                        this, &MainWindow::stopClicked) &&
                connect(dataGeneratorController, &DataGeneratorController::dataReceived,
                        plotWidget, &PlotWidget::appendData);

        if (isConnected)
            return true;
        else
            return false;
    }

    return false;
}

void MainWindow::setButtonIcon(QPushButton *button, const QString &iconPath)
{
//    QPixmap pixmap(iconPath);
//    QIcon buttonIcon(pixmap);
    button->setIcon(QIcon(iconPath));
    button->setIconSize(QSize(50, 50));
    button->setFixedSize(100, 100);
//    button->setIconSize(pixmap.rect().size());
}

void MainWindow::startClicked()
{

    if (dataGeneratorController)
    {
        if (state == State::STOPPED)
            dataGeneratorController->start();
        else if (state == State::SUSPENDED)
            dataGeneratorController->resume();
        else
            return;

        state = State::STARTED;
        start->setEnabled(false);
        pause->setEnabled(true);
        stop->setEnabled(true);
    }
}

void MainWindow::pauseClicked()
{
    if (dataGeneratorController)
    {
        dataGeneratorController->suspend();
        state = State::SUSPENDED;

        start->setEnabled(true);
        pause->setEnabled(false);
        stop->setEnabled(true);
    }
}

void MainWindow::stopClicked()
{
    if (dataGeneratorController)
    {
        dataGeneratorController->stop();
        plotWidget->clearData();
        state = State::STOPPED;

        start->setEnabled(true);
        pause->setEnabled(false);
        stop->setEnabled(false);
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About",
                       QString("QCustomPlot ") + QCUSTOMPLOT_VERSION_STR + "(GPLv3)\n"
                       "Icons from https://icons8.com");
}


void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, "About Qt");
}

