#pragma once

#include <SFML/Graphics.hpp>

template <typename modelT>
class Control
{
protected:
	modelT* model{ nullptr };

protected:
	Control(modelT* m);
	~Control();

public:
	virtual void draw(sf::RenderWindow* w) = 0;
	virtual void buildGeometry() = 0;
	virtual void updateGeometryPosition(sf::RenderWindow* w) = 0;
};

template <typename modelT>
Control<modelT>::Control(modelT* m)
	: model(m)
{

}

template <typename modelT>
Control<modelT>::~Control()
{
	model = nullptr;
}