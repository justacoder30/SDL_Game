#include "Vector.h"

Vector& Vector::operator+=(Vector const& v2)
{
    x += + v2.x;
    y += v2.y;
    return *this;
}

Vector Vector::operator+(Vector const& v2)
{
    return Vector(x + v2.x, y + v2.y);
}

Vector Vector::operator+(float num)
{
    float X = x + num;
    float Y = y + num;
    return Vector(X, Y);
}

Vector Vector::operator*(float num)
{
    return Vector(x * num, y * num);
}

void Vector::printf()
{
    std::cout << "(" << x << ", " << y << ")" << std::endl;
}
