#pragma once

#include <iostream>

#include <qapplication.h>
#include <qwindow.h>

#include "common.h"
#include "vc.h"

class App
{
private:
	VC* vc = nullptr;
	QApplication* a = nullptr;

public:
	App();
	~App();

	void onInit(int argc, char* argv[]);
	void exec();

private:

};
