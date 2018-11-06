#pragma once
namespace Math {
	class Vector3f
	{
	public:
		Vector3f();
		Vector3f(float x, float y, float z);

		Vector3f add(Vector3f vector);
		Vector3f substract(Vector3f vector);

		Vector3f operator+(const Vector3f other);
		Vector3f operator-(const Vector3f other);

		float x;
		float y;
		float z;
	};
}
