#pragma once

#include <cmath>

namespace Math {
	template<typename T>
	class Vector3 {
	public:
		Vector3() : Vector3(0, 0, 0) {};

		Vector3(T x, T y, T z) : x(x), y(y), z(z) {};

		constexpr Vector3<T> add(const Vector3<T> &vector) {
			x += vector.x;
			y += vector.y;
			z += vector.z;
			return *this;
		}

		constexpr Vector3 substract(const Vector3<T> &vector) {
			x += vector.x;
			y += vector.y;
			z += vector.z;
			return *this;
		};

		constexpr Vector3<T> operator+(const Vector3<T> other) {
			Vector3<T> vector;
			vector.x = this->x + other.x;
			vector.y = this->y + other.y;
			vector.z = this->z + other.z;
			return vector;
		};

		constexpr Vector3<T> operator-(const Vector3<T> other) {
			Vector3<T> vector;
			vector.x = this->x - other.x;
			vector.y = this->y - other.y;
			vector.z = this->z - other.z;
			return vector;
		};

		constexpr Vector3<T> normalize() {
			if (length() != 0) {
				x = x / length();
				y = y / length();
				z = z / length();
			}
			return *this;
		};

		constexpr T length() const { return std::sqrt((x * x) + (y * y) + (z * z)); }


		T x;
		T y;
		T z;
	};

	typedef Vector3<float> Vector3f;
	typedef Vector3<double> Vector3d;
	typedef Vector3<int> Vector3i;
	typedef Vector3<unsigned> Vector3u;
}
