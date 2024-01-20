#include "chartWidget.h"

ChartWidget::ChartWidget(QWidget* parent)
	: QWidget(parent)
{

}

void ChartWidget::setData(const QVector<int>& data)
{
    chartData = data;
    update();
}

void ChartWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.drawLine(0, 10, 
        10, 200);
    if (chartData.size() < 2) {
        // Not enough data points to draw a line chart
        return;
    }

    int stepX = width() / (chartData.size() - 1);
    int maxY = *std::max_element(chartData.begin(), chartData.end());

    for (int i = 1; i < chartData.size(); ++i) {
        int x1 = (i - 1) * stepX;
        int y1 = height() - (height() * chartData[i - 1] / maxY);

        int x2 = i * stepX;
        int y2 = height() - (height() * chartData[i] / maxY);

        painter.drawLine(x1, y1, x2, y2);
    }
}

void ChartWidget::resizeEvent(QResizeEvent* event)
{
    setMinimumSize(QSize(200, 200));
}