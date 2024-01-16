#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

template <typename modelT, typename controlT>
class GroupControl
{
protected:
	sf::RenderWindow* window{ nullptr };
	std::vector<controlT*> controls;

public:
	GroupControl(sf::RenderWindow* w);
	~GroupControl();

public:
	virtual void buildControl(modelT* model) = 0;
	void buildControl(controlT* control);

public:
	void draw();

};

template <typename modelT, typename controlT>
GroupControl<modelT, controlT>::GroupControl(sf::RenderWindow* w)
	: window(w)
{

}

template <typename modelT, typename controlT>
GroupControl<modelT, controlT>::~GroupControl()
{
	for (controlT* control : controls)
	{
		delete control;
		control = nullptr;
	}
	controls.clear();
}

template <typename modelT, typename controlT>
void GroupControl<modelT, controlT>::buildControl(controlT* control)
{
	control->buildGeometry();
	controls.push_back(control);
}

template <typename modelT, typename controlT>
void GroupControl<modelT, controlT>::draw()
{
	for (controlT* control : controls)
	{
		control->updateGeometryPosition(window);
		control->draw(window);
	}
}