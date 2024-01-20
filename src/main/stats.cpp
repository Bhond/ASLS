#include "stats.h"

Stats::Stats(QWidget* parent)
	: QWidget(parent)
{
}

Stats::~Stats()
{
	delete mainLayout;
	delete populationSizeChart;
}

void Stats::onInit()
{	
	mainLayout = new QGridLayout(this);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setSpacing(0);

	populationSizeChart = new ChartWidget();
	populationSizeChart->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding));

	QPushButton* test = new QPushButton("Test", this);
	test->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding));

	mainLayout->addWidget(test, 0, 1, 1, 1);
	mainLayout->addWidget(populationSizeChart, 0, 0, 1, 1);
	populationSizeChart->setData(QVector<int>{20, 50, 30, 80, 60, 40, 90, 10});
}

void Stats::paintEvent(QPaintEvent* event)
{
}

void Stats::addPopulationSizeUpdate(int v)
{
	populationSize.push_back(v);
}

void Stats::clearPopulationSize()
{
	populationSize.clear();
}
