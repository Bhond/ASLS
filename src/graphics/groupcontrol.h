#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "control.h"

template <typename modelT>
class GroupControl
{
protected:
	std::vector<std::shared_ptr<Control<modelT>>> controls;

public:
	GroupControl() = default;
	~GroupControl() = default;

public:
	virtual void buildControl(std::shared_ptr<modelT> model) = 0;
	void buildControl(std::shared_ptr<Control<modelT>> control);

public:
	void draw();
	void computeHitBoxes(std::shared_ptr<sf::RenderWindow> w);
	modelT* hasHitAControl(const int& x, const int& y);

};

template <typename modelT>
void GroupControl<modelT>::buildControl(std::shared_ptr<Control<modelT>> control)
{
	control->buildGeometry();
	controls.push_back(control);
}

template <typename modelT>
void GroupControl<modelT>::draw()
{
	for (std::shared_ptr<Control<modelT>>& control : controls)
	{
		control->updateGeometryPosition(window);
		control->onSelected(window);
		control->draw(window);
	}
}

template <typename modelT>
void GroupControl<modelT>::computeHitBoxes(std::shared_ptr<sf::RenderWindow> w)
{
	for (std::shared_ptr<Control<modelT>> control : controls)
	{
		control->computeHitBox(w);
	}
}

template <typename modelT>
modelT* GroupControl<modelT>::hasHitAControl(const int& x, const int& y)
{
	for (std::shared_ptr<Control<modelT>> control : controls)
	{
		if (control->isHit(x, y))
		{
			return control->getModel();
		}
	}
	return nullptr;
}