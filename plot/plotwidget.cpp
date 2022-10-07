#include "plotwidget.h"

PlotWidget::PlotWidget(QWidget *parent)
    : QWidget{parent},
      plot(new QCustomPlot(this))
{
    QLayout *layout = new QVBoxLayout(this);
    layout->addWidget(plot);
}
