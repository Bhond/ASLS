#include "labelvaluepair.h"

LabelValuePair::LabelValuePair(const Orientation& o,
	const std::string& l,
	const double& initialValue,
	QWidget* parent)
	: orientation(o),
	label(l),
	value(initialValue),
	QWidget(parent)
{
	init(o, label);
}

LabelValuePair::LabelValuePair(const std::string& l,
	const double& initialValue,
	QWidget* parent)
	: label(l),
	value(initialValue),
	QWidget(parent)
{
	init(LabelValuePair::Orientation::HORIZONTAL, l);
}

void LabelValuePair::init(const LabelValuePair::Orientation& o, const std::string& l)
{
	// Build root layout depending on wanted orientation
	switch (o)
	{
	case LabelValuePair::Orientation::HORIZONTAL:
		root = new QHBoxLayout(this);
		break;

	case LabelValuePair::Orientation::VERTICAL:
		root = new QVBoxLayout(this);
		break;
	}
	root->setAlignment(Qt::AlignmentFlag::AlignCenter);

	// Build widgets and initialize them
	labelWidget = new QLabel(this);
	labelWidget->setAlignment(Qt::AlignmentFlag::AlignCenter);
	labelWidget->setText(l.c_str());

	valueWidget = new QLineEdit(this);
	valueWidget->setAlignment(Qt::AlignmentFlag::AlignCenter);
	connect(valueWidget, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
	update();

	root->addWidget(labelWidget);
	root->addWidget(valueWidget);
}

LabelValuePair::~LabelValuePair()
{
	delete(root);
	delete(labelWidget);
	delete(valueWidget);
}

void LabelValuePair::update()
{
	oss.clear();
	oss.str(std::string());
	oss << value << std::endl;
	valueWidget->clear();
	valueWidget->setText(oss.str().c_str());
}

double LabelValuePair::getValue()
{
	return value;
}

void LabelValuePair::setValue(const double& v)
{
	value = v;
	update();
}

void LabelValuePair::onValueChanged()
{
	bool validated = false;
	double newValue = valueWidget->text().toDouble(&validated);

	if (!validated)
	{
		update();
	}
	else if (value != newValue)
	{
		setValue(newValue);
		emit valueChanged();
	}
}