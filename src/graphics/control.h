#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../main/mymath.h"

template <typename modelT>
class Control
{
protected:
	std::vector<sf::Shape*> shapes;
	std::vector<float> hitBox;
	bool selected{ false };
	std::shared_ptr<modelT> model{ nullptr };

public:
	~Control();

protected:
	Control(std::shared_ptr<modelT> m);

public:
	virtual void draw(std::shared_ptr<sf::RenderWindow> w) = 0;
	virtual void buildGeometry() = 0;
	virtual void updateGeometryPosition(std::shared_ptr<sf::RenderWindow> w) = 0;
	virtual void onSelected(std::shared_ptr<sf::RenderWindow> w);

public:
	void computeHitBox(std::shared_ptr<sf::RenderWindow> w);

public:
	bool isSelected();
	bool isHit(const int& x, const int& y);
	std::shared_ptr<modelT>& getModel();
	Vector2 decode(const Vector2& v);
	sf::Vector2f toVector2f(const Vector2& v);


public:
	void setSelected(bool b);
};

template <typename modelT>
Control<modelT>::Control(std::shared_ptr<modelT> m)
	: model(m)
{
	hitBox.push_back(0.0f);
	hitBox.push_back(0.0f);
	hitBox.push_back(0.0f);
	hitBox.push_back(0.0f);
}

template <typename modelT>
Control<modelT>::~Control()
{
	model = nullptr; // Destroyed elsewhere
	for (sf::Shape* s : shapes)
	{
		delete s;
	}
	shapes.clear();
}

template <typename modelT>
void Control<modelT>::computeHitBox(std::shared_ptr<sf::RenderWindow> w)
{
	float minX{ (float)w->getSize().x };
	float maxX{ 0.0f };
	float minY{ (float)w->getSize().y };
	float maxY{ 0.0f };
	for (sf::Shape* s : shapes)
	{
		for (size_t i = 0; i < s->getPointCount(); i++)
		{
			sf::Vector2f p = s->getPoint(i);

			float x = p.x;
			float y = p.y;

			minX = std::min(minX, x);
			maxX = std::max(maxX, x);
			minY = std::min(minY, y);
			maxY = std::max(maxY, y);
		}
	}
	hitBox[0] = minX;
	hitBox[1] = maxX;
	hitBox[2] = minY;
	hitBox[3] = maxY;
}

template <typename modelT>
void Control<modelT>::onSelected(std::shared_ptr<sf::RenderWindow> w){}

template <typename modelT>
bool Control<modelT>::isSelected()
{
	return selected;
}

template <typename modelT>
bool Control<modelT>::isHit(const int& x, const int& y)
{
	bool hit = (x >= hitBox[0] && x <= hitBox[1]) && (y >= hitBox[2] && y <= hitBox[3]);
	selected = hit;
	return hit;
}

template <typename modelT>
void Control<modelT>::setSelected(bool b)
{
	selected = b;
}

template <typename modelT>
std::shared_ptr<modelT>& Control<modelT>::getModel()
{
	return model;
}

template<typename modelT>
Vector2 Control<modelT>::decode(const Vector2& v)
{
	return Vector2(v.x, -v.y);
}

template<typename modelT>
sf::Vector2f Control<modelT>::toVector2f(const Vector2& v)
{
	return sf::Vector2f((float)v.x, (float)v.y);
}