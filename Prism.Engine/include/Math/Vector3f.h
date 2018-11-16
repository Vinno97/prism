#pragma once
namespace Math {
	class Vector3f
	{
	public:
		Vector3f();
		Vector3f(float x, float y, float z);

		Vector3f add(const Vector3f& vector);
		Vector3f substract(const Vector3f& vector);
		//Vector3f normalize(const Vector3f& vector);

		Vector3f operator+(const Vector3f other);
		Vector3f operator-(const Vector3f other);

		float x;
		float y;
		float z;
	};
}
