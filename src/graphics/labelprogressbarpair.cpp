#include "labelprogressbarpair.h"

LabelProgressbarPair::LabelProgressbarPair(const Orientation& o,
	const std::string& l,
	const double& initialProgress,
	QWidget* parent)
	: orientation(o),
	label(l),
	progress(initialProgress),
	QWidget(parent)
{
	init(o, label);
}

LabelProgressbarPair::LabelProgressbarPair(const std::string& l,
	const double& initialPogress,
	QWidget* parent)
	: label(l),
	progress(initialPogress),
	QWidget(parent)
{
	init(LabelProgressbarPair::Orientation::HORIZONTAL, l);
}

LabelProgressbarPair::~LabelProgressbarPair()
{
	delete root;
	delete labelWidget;
	delete barWidget;
}

void LabelProgressbarPair::init(const LabelProgressbarPair::Orientation& o, const std::string& l)
{
	// Build root layout depending on wanted orientation
	switch (o)
	{
	case LabelProgressbarPair::Orientation::HORIZONTAL:
		root = new QHBoxLayout(this);
		break;

	case LabelProgressbarPair::Orientation::VERTICAL:
		root = new QVBoxLayout(this);
		break;
	}
	root->setAlignment(Qt::AlignmentFlag::AlignCenter);

	// Build widgets and initialize them
	labelWidget = new QLabel(this);
	labelWidget->setAlignment(Qt::AlignmentFlag::AlignCenter);
	labelWidget->setText(l.c_str());

	barWidget = new QProgressBar(this);
	barWidget->setAlignment(Qt::AlignmentFlag::AlignCenter);
	connect(barWidget, SIGNAL(valueChanged(int)), this, SLOT(onProgressChanged()));
	update();

	root->addWidget(labelWidget);
	root->addWidget(barWidget);
}

void LabelProgressbarPair::update()
{
	barWidget->setValue(progress);
}

double LabelProgressbarPair::getProgress()
{
	return progress;
}

void LabelProgressbarPair::setProgress(const double& v)
{
	progress = v;
	update();
}

void LabelProgressbarPair::onProgressChanged()
{
	bool validated = false;
	double newProgress = barWidget->text().toDouble(&validated);

	if (!validated)
	{
		update();
	}
	else if (progress != newProgress)
	{
		setProgress(newProgress);
		emit progressChanged();
	}
}