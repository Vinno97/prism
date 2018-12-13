#include <cmath>

#pragma once
namespace Math
{
	template <typename T>
	class Vector2
	{
	public:
		Vector2() = default;;

		Vector2(T x_, T y_) : x(x_), y(y_)
		{
		};

		Vector2 add(const Vector2<T>& other) const
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		Vector2 substract(const Vector2<T>& other) const
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		Vector2 operator+(const Vector2<T>& other) const
		{
			Vector2 vector;
			vector.x = this->x + other.x;
			vector.y = this->y + other.y;
			return vector;
		}

		Vector2 operator-(const Vector2<T>& other) const
		{
			Vector2 vector;
			vector.x = this->x - other.x;
			vector.y = this->y - other.y;
			return vector;
		}

		Vector2 operator*(const Vector2<T>& other) const
		{
			Vector2 vector;
			vector.x = this->x - other.x;
			vector.y = this->y - other.y;
			return vector;
		}

		Vector2 normalize()
		{
			T length = length();
			if (length != 0)
			{
				x = x / length;
				y = y / length;
			}
			return *this;
		}

		constexpr T length() const { return std::sqrt((x * x) + (y * y)); }

		T x{0};
		T y{0};
	};


	template <typename T>
	constexpr T distance(const Vector2<T>& vector1, const Vector2<T>& vector2)
	{
		return (vector1 - vector2).length();
	}
}
