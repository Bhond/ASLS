#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include <qwidget.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qboxlayout.h>

class LabelValuePair : public QWidget
{
	Q_OBJECT

public:
	const enum class Orientation { HORIZONTAL, VERTICAL };

private:
	Orientation orientation;
	std::string label = "";
	double value;
	std::ostringstream oss;

	QBoxLayout* root = nullptr;
	QLabel* labelWidget = nullptr;
	QLineEdit* valueWidget = nullptr;

public:
	LabelValuePair(const Orientation& o,
		const std::string& l,
		const double& initialValue,
		QWidget* parent = 0);
	LabelValuePair(const std::string& l,
		const double& initialValue,
		QWidget* parent = 0);
	~LabelValuePair();
	void init(const LabelValuePair::Orientation& o, const std::string& l);

private:
	void update();

public:
	double getValue();
	void setValue(const double& value);

public slots:
	void onValueChanged();

signals:
	void valueChanged();
};
