#pragma once

#include <iostream>
#include <math.h>

const double Epsilon = 1e-7;
const double PI = 2*acos(0.0);

struct Vector2
{
public:
	double x {0};
	double y {0};

public:
	Vector2()
	{

	}

	Vector2(double xx, double yy)
		: x(xx), y(yy)
	{

	}

	Vector2 operator+(const Vector2& u) const
	{
		return Vector2{ x + u.x, y + u.y };
	}

	Vector2& operator+=(const Vector2& u)
	{
		x += u.x;
		y += u.y;
		return *this;
	}

	Vector2 operator-(const Vector2& u) const
	{
		return Vector2{ x - u.x, y - u.y };
	}

	Vector2& operator-=(const Vector2& u) 
	{
		x -= u.x;
		y -= u.y;
		return *this;
	}

	Vector2 operator*(const double& a) const
	{
		return Vector2{ a * x, a * y };
	}

	Vector2 operator/(const double& a) const
	{
		return Vector2{ x / a, y / a };
	}

	Vector2& operator*=(const double& a)
	{
		x *= a;
		y *= a;
		return *this;
	}

	bool operator==(const Vector2& other) const
	{
		return x == other.x && y == other.y;
	}

public:
	double length2()
	{
		return x * x + y * y;
	}

	double length()
	{
		return sqrt(length2());
	}

	Vector2 unit()
	{
		double d = length();
		if (fabs(d) < Epsilon)
			return Vector2{ .0, .0 };
		else
			return Vector2 { x / d, y / d };
	}

public:
	static double dot(const Vector2& u, const Vector2& v)
	{
		return u.x * v.x + u.y * v.y;
	}

	static Vector2 rotate(const Vector2& u, const double& angle_rad)
	{
		return Vector2(
			u.x * cos(angle_rad) - u.y * sin(angle_rad),
			u.x * sin(angle_rad) + u.y * cos(angle_rad)		
		);
	}

};
