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

    if( initGUI()  == false )
        return;

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::initGUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget());
    QLayout *buttonsLayout = new QHBoxLayout(this);

    if(
            mainLayout &&
            buttonsLayout &&
            plotWidget &&
            start &&
            pause &&
            stop )
    {
        mainLayout->addWidget(plotWidget);
        buttonsLayout->addWidget(start);
        buttonsLayout->addWidget(pause);
        buttonsLayout->addWidget(stop);
        mainLayout->addLayout(buttonsLayout);

        return true;
    }

    return false;
}
