#include "plotwidget.h"

PlotWidget::PlotWidget(QWidget *parent)
    : QWidget{parent},
      plot(new QCustomPlot(this))
{
    QLayout *layout = new QVBoxLayout(this);
    layout->addWidget(plot);

    graph = plot->addGraph();
    setDefaultRange();
    setPlotStyle();
}

void PlotWidget::appendData(const double x, const double y)
{
    if (plot && graph)
    {
        qInfo() << "Appending data (x, y): " << x << " " << y;
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

void PlotWidget::setPlotStyle()
{
    if (plot && graph)
    {
        // stylesheet from 'styled plot demo'
        graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(QColor(82, 237, 250)), 9));
        graph->setLineStyle(QCPGraph::lsNone);
        graph->setPen(QPen(QColor(120, 120, 120), 2));
        setAxisStyle(plot->xAxis);
        setAxisStyle(plot->xAxis2);
        setAxisStyle(plot->yAxis);
        setAxisStyle(plot->yAxis2);

        QLinearGradient plotGradient;
        plotGradient.setStart(0, 0);
        plotGradient.setFinalStop(0, 350);
        plotGradient.setColorAt(0, QColor(80, 80, 80));
        plotGradient.setColorAt(1, QColor(50, 50, 50));
        plot->setBackground(plotGradient);
        QLinearGradient axisRectGradient;
        axisRectGradient.setStart(0, 0);
        axisRectGradient.setFinalStop(0, 350);
        axisRectGradient.setColorAt(0, QColor(80, 80, 80));
        axisRectGradient.setColorAt(1, QColor(30, 30, 30));
        plot->axisRect()->setBackground(axisRectGradient);
        plot->xAxis2->setVisible(true);
        plot->yAxis2->setVisible(true);
    }
}

void PlotWidget::setAxisStyle(QCPAxis *axis)
{
    axis->setBasePen(QPen(QColor(230, 230, 230), 1));
    axis->setTickPen(QPen(QColor(230, 230, 230), 1));
    axis->setSubTickPen(QPen(QColor(230, 230, 230), 1));
    axis->setTickLabelColor(QColor(230, 230, 230));
    axis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    axis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    axis->grid()->setSubGridVisible(true);
    axis->grid()->setZeroLinePen(Qt::NoPen);
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
            axis->setRangeLower(value - 1.0);
        else if (value > range.upper)
            axis->setRangeUpper(value + 1.0);
    }
}
