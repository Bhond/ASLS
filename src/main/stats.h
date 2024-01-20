#pragma once

#include <iostream>
#include <vector>

#include <qwidget.h>
#include <qevent.h>
#include <qgridlayout.h>
#include <qpushbutton.h>

#include "../models/genome.h"
#include "../graphics/chartWidget.h"

class Stats : public QWidget
{
private:
	std::vector<int> populationSize;
	
	QGridLayout* mainLayout{ nullptr };
	ChartWidget* populationSizeChart{ nullptr };

public:
	Stats(QWidget* parent = nullptr);
	~Stats();

public:
	void onInit();

protected:
	void paintEvent(QPaintEvent* event) override;

public:
	void addPopulationSizeUpdate(int v);
	void clearPopulationSize();

};