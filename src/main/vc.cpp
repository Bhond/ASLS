#include "vc.h"

VC::VC()
	: QMainWindow()
{
}

VC::~VC()
{
	delete simulation;
	delete playButton;
	delete pauseButton;
	delete resetButton;
	delete scaleWidthField;
	delete scaleHeightField;
	delete overlayBox;
	delete healthBar;
	delete hungerBar;
}

void VC::onInit()
{
	// Parent
	resize(QSize(Width, Height));

	// Init sizes
	float anchorX = 0;
	float anchorY = 0;
	float margin = 10;

	float controlContainerWidth = Width / 4;
	float controlContainerHeight = Height - 2 * anchorY;

	// Simulation
	float posX = anchorX + controlContainerWidth + margin;
	float posY = anchorY;
	float simWidth = Width - posX - anchorX;
	float simHeight = controlContainerHeight;

	simulation = new Simulation(this, QPoint(posX, posY), QSize(simWidth, simHeight), 1);
	simulation->show();

	// Controls
	float controlsX = 0.5 * controlContainerWidth;
	float controlsY = margin;
	float controlsStep = 10;

	playButton = new QPushButton("Play", this);
	float playButtonX = controlsX - playButton->size().width() * 0.5;
	playButton->move(QPoint(playButtonX, controlsY));
	connect(playButton, SIGNAL(clicked()), simulation, SLOT(play()));

	pauseButton = new QPushButton("Pause", this);
	float pauseButtonX = controlsX - pauseButton->size().width() * 0.5;
	controlsY += controlsStep + playButton->size().height();
	pauseButton->move(QPoint(pauseButtonX, controlsY));
	connect(pauseButton, SIGNAL(clicked()), simulation, SLOT(pause()));

	/*resetButton = new QPushButton("Reset", this);
	float resetButtonX = controlsX - resetButton->size().width() * 0.5;
	controlsY += controlsStep + pauseButton->size().height();
	resetButton->move(QPoint(resetButtonX, controlsY));
	connect(resetButton, SIGNAL(clicked()), simulation, SLOT(reset()));*/
	
	healthBar = new LabelProgressbarPair("Health", 100, this);
	healthBar->resize(QSize(std::min(controlContainerHeight - 2 * margin, 300.0f), 70.0));
	float healthBarX = controlsX - healthBar->size().width() * 0.5;
	controlsY += controlsStep + pauseButton->size().height();
	healthBar->move(QPoint(healthBarX, controlsY));
	healthBar->hide();
	//connect(resetButton, SIGNAL(clicked()), simulation, SLOT(reset()));

	hungerBar = new LabelProgressbarPair("Hunger", 0, this);
	hungerBar->resize(QSize(std::min(controlContainerHeight - 2 * margin, 300.0f), 70.0));
	float hungerBarX = controlsX - hungerBar->size().width() * 0.5;
	controlsY += controlsStep + healthBar->size().height();
	hungerBar->move(QPoint(hungerBarX, controlsY));
	hungerBar->hide();
	//connect(resetButton, SIGNAL(clicked()), simulation, SLOT(reset()));

	/*scaleWidthField = new LabelValuePair("Scale width", 1.0, this);
	scaleWidthField->resize(QSize(std::min(controlContainerWidth - 2 * margin, 300.0f), 70.0));
	float scaleWidthFieldX = controlsX - scaleWidthField->size().width() * 0.5;
	controlsY += controlsStep + resetButton->size().height();
	scaleWidthField->move(QPoint(scaleWidthFieldX, controlsY));
	connect(scaleWidthField, SIGNAL(valueChanged()), this, SLOT(onScaleWidthFieldValueChanged()));

	scaleHeightField = new LabelValuePair("Scale height", 1.0, this);
	scaleHeightField->resize(QSize(std::min(controlContainerHeight - 2 * margin, 300.0f), 70.0));
	float scaleHeightFieldX = controlsX - scaleHeightField->size().width() * 0.5;
	controlsY += controlsStep + scaleWidthField->size().height();
	scaleHeightField->move(QPoint(scaleHeightFieldX, controlsY));
	connect(scaleHeightField, SIGNAL(valueChanged()), this, SLOT(onScaleHeightFieldValueChanged()));*/

	// Simulation callbacks
	simulation->setOnEntityModelSelected([this](EntityModel* m)
		{
			if (m)
			{
				healthBar->setProgress(m->health * 100);
				hungerBar->setProgress(m->hunger * 100);
				healthBar->show();
				hungerBar->show();
			}
		});
	simulation->setOnEntityModelDeselected([this](EntityModel* m)
		{
				healthBar->hide();
				hungerBar->hide();
		});
	simulation->setOnSimulationRenderTick([this](EntityModel* m)
		{
			if (m)
			{
				healthBar->setProgress(m->health * 100);
				hungerBar->setProgress(m->hunger * 100);
			}
		});


}

void VC::display()
{
	this->show();
}

void VC::onScaleWidthFieldValueChanged()
{
	simulation->setScaleWidth(scaleWidthField->getValue());
}

void VC::onScaleHeightFieldValueChanged()
{
	simulation->setScaleHeight(scaleHeightField->getValue());
}