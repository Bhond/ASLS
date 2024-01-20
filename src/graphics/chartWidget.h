#pragma once

#include <iostream>

#include <qwidget.h>
#include <qvector.h>
#include <qpainter.h>

class ChartWidget : public QWidget
{
private:
    QVector<int> chartData;

public:
	ChartWidget(QWidget* parent = 0);

public:
    void setData(const QVector<int>& data);

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

};