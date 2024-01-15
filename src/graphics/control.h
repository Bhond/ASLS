#pragma once

template <typename modelT>
class Control
{
protected:
	modelT* model{ nullptr };

protected:
	Control(modelT* m);
	~Control();

public:
	virtual void draw() = 0;
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