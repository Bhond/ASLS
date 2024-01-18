#pragma once

#include <qwidget.h>
#include "qboxlayout.h"
#include <qlabel.h>
#include <qprogressbar.h>

class LabelProgressbarPair : public QWidget
	{
		Q_OBJECT

	public:
		const enum class Orientation { HORIZONTAL, VERTICAL };

	private:
		Orientation orientation;
		std::string label = "";
		double progress;
		//std::ostringstream oss;

		QBoxLayout* root = nullptr;
		QLabel* labelWidget = nullptr;
		QProgressBar* barWidget = nullptr;

	public:
		LabelProgressbarPair(const Orientation& o,
			const std::string& l,
			const double& initialProgress,
			QWidget* parent = 0);
		LabelProgressbarPair(const std::string& l,
			const double& initialProgress,
			QWidget* parent = 0);
		~LabelProgressbarPair();
		void init(const LabelProgressbarPair::Orientation& o, const std::string& l);

	private:
		void update();

	public:
		double getProgress();
		void setProgress(const double& progress);

	public slots:
		void onProgressChanged();

	signals:
		void progressChanged();
};