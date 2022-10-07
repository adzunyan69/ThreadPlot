#include "plotwidget.h"

PlotWidget::PlotWidget(QWidget *parent)
    : QWidget{parent},
      plot(new QCustomPlot(this))
{
    QLayout *layout = new QVBoxLayout(this);
    layout->addWidget(plot);

    graph = plot->addGraph();
    setDefaultRange();
}

void PlotWidget::appendData(const double x, const double y)
{
    if (plot && graph)
    {
        graph->addData(x, y);
        adjustAxes(x, y);

        plot->replot();
    }
}

void PlotWidget::clearData()
{
    if (graph)
    {
        graph->data()->clear();
        setDefaultRange();

        if (plot)
            plot->replot();
    }
}

void PlotWidget::setDefaultRange()
{
    if (plot)
    {
        plot->xAxis->setRange(xDefaultRange);
        plot->yAxis->setRange(yDefaultRange);
    }
}

void PlotWidget::adjustAxes(const double x, const double y)
{
    if (plot)
    {
        adjustAxis(plot->xAxis, x);
        adjustAxis(plot->yAxis, y);
    }
}

void PlotWidget::adjustAxis(QCPAxis *axis, const double value)
{
    if (axis)
    {
        auto range = axis->range();

        if (value < range.lower)
            axis->setRangeLower(value);
        else if (value > range.upper)
            axis->setRangeUpper(value);
    }
}
