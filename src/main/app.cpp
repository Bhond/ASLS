#include "app.h"

App::App()
{
}

App::~App()
{
	delete a;
}

void App::onInit(int argc, char* argv[])
{
	a = new QApplication(argc, argv);

	QFile styleFile(PATH_ROOT"/res/theme.qss" );
	styleFile.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(styleFile.readAll());
	a->setStyleSheet(styleSheet);

	vc = new VC();
	vc->onInit();
}

void App::exec()
{
	vc->display();
	a->exec();
}

