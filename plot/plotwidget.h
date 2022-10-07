#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>

#include "QCustomPlot/qcustomplot.h"

class PlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlotWidget(QWidget *parent = nullptr);

private:
    QCustomPlot *plot{ nullptr };

signals:

};

#endif // PLOTWIDGET_H
