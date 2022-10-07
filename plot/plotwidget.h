#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>

#include "QCustomPlot/qcustomplot.h"

class PlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlotWidget(QWidget *parent = nullptr);


public slots:
    void appendData(const double x, const double y);
    void clearData();

private:
    const QCPRange xDefaultRange{ -1.0, 1.0 };
    const QCPRange yDefaultRange{ -1.0, 1.0 };

    QCustomPlot *plot{ nullptr };
    QCPGraph *graph{ nullptr };

    void setDefaultRange();
    void setPlotStyle();
    void setAxisStyle(QCPAxis *axis);
    void adjustAxes(const double x, const double y);
    void adjustAxis(QCPAxis *axis, const double value);

signals:

};

#endif // PLOTWIDGET_H
