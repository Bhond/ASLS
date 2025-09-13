#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "control.hpp"

template <typename modelT>
class GroupControl
{
protected:
	std::vector<Control<modelT>*> controls;

public:
	GroupControl() = default;
	~GroupControl();

public:
	virtual void buildControl(modelT* model) = 0;
	void buildControl(Control<modelT>* control);
	void deleteControl(modelT* model);

public:
	void draw(sf::RenderWindow& window);
	void computeHitBoxes(sf::RenderWindow& w);
	modelT* hasHitAControl(const int& x, const int& y);

};

template <typename modelT>
GroupControl<modelT>::~GroupControl() 
{
	std::cout << "Deleting: " << this << std::endl;
	// Remove all controls
	for (Control<modelT>* c : controls)
	{
		c = nullptr;
		delete c;
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
void GroupControl<modelT>::draw(sf::RenderWindow& window)
{
	for (Control<modelT>*& control : controls)
	{
		control->updateGeometryPosition(window);
		control->onSelected(window);
		control->draw(window);
	}
}

template <typename modelT>
void GroupControl<modelT>::computeHitBoxes(sf::RenderWindow& w)
{
	for (Control<modelT>*&  control : controls)
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

template <typename modelT>
void GroupControl<modelT>::deleteControl(modelT* model)
{
	// Find control
	Control<modelT>* toDelete{nullptr};
	for (Control<modelT>*& control : controls)
	{
		if (control->getModel() == model)
		{
			toDelete = control;
			break;
		}
	}
	// Remove from vector
	controls.erase(std::remove(controls.begin(), controls.end(), toDelete), controls.end());
	// Clean
	delete toDelete;
	toDelete = nullptr;
}