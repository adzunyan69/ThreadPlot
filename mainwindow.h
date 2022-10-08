#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

#include "plot/plotwidget.h"
#include "generator/datageneratorcontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    enum class State { STOPPED, STARTED, SUSPENDED };
    State state{ State::STOPPED };

    Ui::MainWindow *ui;
    PlotWidget *plotWidget{ nullptr };
    DataGeneratorController *dataGeneratorController{ nullptr };
    QPushButton *start{ nullptr };
    QPushButton *pause{ nullptr };
    QPushButton *stop{ nullptr };

    bool initGUI();

private slots:
    void startClicked();
    void pauseClicked();
    void stopClicked();
};
#endif // MAINWINDOW_H
