#pragma once

#include <iostream>
#include <vector>

template <typename modelT, typename controlT>
class GroupControl
{
protected:
	std::vector<controlT*> controls;

public:
	GroupControl();
	~GroupControl();

public:
	virtual void buildControl(modelT* model) = 0;
	void buildControl(controlT* control);

public:
	void draw();

};

template <typename modelT, typename controlT>
GroupControl<modelT, controlT>::GroupControl()
{

}

template <typename modelT, typename controlT>
GroupControl<modelT, controlT>::~GroupControl()
{
	for (controlT* control : controls)
	{
		delete control;
	}
}

template <typename modelT, typename controlT>
void GroupControl<modelT, controlT>::buildControl(controlT* control)
{
	controls.push_back(control);
}

template <typename modelT, typename controlT>
void GroupControl<modelT, controlT>::draw()
{
	for (controlT* control : controls)
	{
		control->draw();
	}
}