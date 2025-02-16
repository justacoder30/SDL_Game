#pragma once


class Vector
{
public:
	Vector(float X=0, float Y=0) : x(X), y(Y) {}
	float x, y;
	Vector& operator+=(Vector const& v2);
	Vector operator+(Vector const& v2);
	Vector operator+(float num);
	Vector operator*(float num);
	void printf();
};

