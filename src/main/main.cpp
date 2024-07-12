#include "app.h"

int main(int argc, char* argv[])
{
	App a;
	a.onInit(argc, argv);
	return a.exec();
}