#include "Math/Vector3f.h"
#include <math.h>
Math::Vector3f::Vector3f() {
    x = 0;
    y = 0;
}

Math::Vector3f::Vector3f(float x, float y, float z) : x{ x }, y{ y }, z{ z } {

}

Math::Vector3f Math::Vector3f::add(const Math::Vector3f& vector) {
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
}

Math::Vector3f Math::Vector3f::substract(const Math::Vector3f& vector) {
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
}



Math::Vector3f Math::Vector3f::operator+(const Math::Vector3f other) {
    Vector3f vector;
    vector.x = this->x + other.x;
    vector.y = this->y + other.y;
    vector.z = this->z + other.z;
    return vector;
}

Math::Vector3f Math::Vector3f::operator-(const Math::Vector3f other) {
    Vector3f vector;
    vector.x = this->x - other.x;
    vector.y = this->y - other.y;
    vector.z = this->z - other.z;
    return vector;
}

Math::Vector3f Math::Vector3f::normalize()
{
	float lenght = sqrt((x*x) + (y*y)+ (z*z));
	x = x / lenght;
	y = y / lenght;
	z = z / lenght;
	return *this;
}

