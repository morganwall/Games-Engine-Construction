#pragma once
#include <cmath>

namespace sf // Forward declaration of the sfml templated vector class, so that I can convert it to my vector2.
{
	template <class T>
	class Vector2;
}

template <class T> // Template to allow the use of multiple data types.
class Vector2
{
public:
	T x{}, y{};
	T length{}; // The length/magnitude of the vector.
	T direction{}; // The direction of the vector.

	// Return the length of the vector.
	float Length() { return float(sqrt(x * x + y * y)); }
	// Return a normalized version of the vector, using division. This is slow.
	Vector2 Normalize() { return { x / length, y / length }; }
	// Return a normalized version of the vector, using multiplication. This is faster.
	Vector2 FastNormalize()
	{
		T inverse{ 1.0f / length }; // The inverse length.
		return { x * inverse, y * inverse };
	}

	// Addition.
	Vector2 operator+(const Vector2& vector) { return Vector2(x + vector.x, y + vector.y); }
	// Subtraction.
	Vector2 operator-(const Vector2& vector) { return Vector2(x - vector.x, y - vector.y); }
	// Multiplication.
	Vector2 operator*(const Vector2& vector) { return Vector2(x * vector.x, y * vector.y); }
	// Division.
	Vector2 operator/(const Vector2& vector) { return Vector2(x / vector.x, y / vector.y); }
	// Addition Equals.
	Vector2 operator+=(const Vector2& vector)
	{
		x += vector.x;
		y += vector.y;
		return *this;
	}
	// Subtraction Equals.
	Vector2 operator-=(const Vector2& vector)
	{
		x -= vector.x;
		y -= vector.y;
		return *this;
	}
	// Multiplication Equals.
	Vector2 operator*=(const Vector2& vector)
	{
		x *= vector.x;
		y *= vector.y;
		return *this;
	}
	// Division Equals.
	Vector2 operator/=(const Vector2& vector)
	{
		x /= vector.x;
		y /= vector.y;
		return *this;
	}
	// Scalar Addition.
	Vector2 operator+(const T& scalar)
	{
		x += scalar;
		y += scalar;
		return *this;
	}
	// Scalar Subtraction.
	Vector2 operator-(const T& scalar)
	{
		x -= scalar;
		y -= scalar;
		return *this;
	}
	// Scalar Multiplication.
	Vector2 operator*(const T& scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}
	// Scalar Division.
	Vector2 operator/(const T& scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}
	// Convert from sf::Vector2.
	Vector2 operator=(const sf::Vector2<T>& vector)
	{
		x = vector.x;
		y = vector.y;
		return *this;
	}

	// Constructors.
	Vector2(T X, T Y) : x(X), y(Y), length(Length()) {}
	// Create a Vector2 from an sf::Vector2.
	Vector2(const sf::Vector2<T>& vector) : x(vector.x), y(vector.y), length(Length()) {}
	Vector2() {}
};