#pragma once


class Vector
{
public:
	Vector(const float& X=0, const float& Y=0) : x(X), y(Y) {}
	float x, y;
	static Vector zero();
	static Vector all(const float& size);
	Vector& operator+=(Vector const& v2);
	Vector operator+(Vector const& v2);
	Vector operator+(const float& num);
	Vector operator*(const float& num);
	Vector operator/(const float& num);
	void printf();
};

