#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "control.h"

template <typename modelT>
class GroupControl
{
protected:
	sf::RenderWindow* window{ nullptr };
	std::vector<Control<modelT>*> controls;

public:
	GroupControl(sf::RenderWindow* w);
	~GroupControl();

public:
	virtual void buildControl(modelT* model) = 0;
	void buildControl(Control<modelT>* control);

public:
	void draw();
	void computeHitBoxes(sf::RenderWindow* w);
	modelT* hasHitAControl(const int& x, const int& y);

};

template <typename modelT>
GroupControl<modelT>::GroupControl(sf::RenderWindow* w)
	: window(w)
{

}

template <typename modelT>
GroupControl<modelT>::~GroupControl()
{
	for (Control<modelT>* control : controls)
	{
		delete control;
		control = nullptr;
	}
	controls.clear();
}

template <typename modelT>
void GroupControl<modelT>::buildControl(Control<modelT>* control)
{
	control->buildGeometry();
	controls.push_back(control);
}

template <typename modelT>
void GroupControl<modelT>::draw()
{
	for (Control<modelT>* control : controls)
	{
		control->updateGeometryPosition(window);
		control->onSelected(window);
		control->draw(window);
	}
}

template <typename modelT>
void GroupControl<modelT>::computeHitBoxes(sf::RenderWindow* w)
{
	for (Control<modelT>* control : controls)
	{
		control->computeHitBox(w);
	}
}

template <typename modelT>
modelT* GroupControl<modelT>::hasHitAControl(const int& x, const int& y)
{
	for (Control<modelT>* control : controls)
	{
		if (control->isHit(x, y))
		{
			return control->getModel();
		}
	}
	return nullptr;
}