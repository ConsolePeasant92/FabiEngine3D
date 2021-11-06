#pragma once

#include <cmath>

struct Vec2;

struct Ivec2 final
{
	Ivec2();
	Ivec2(const Vec2& other);
	Ivec2(const int value);
	Ivec2(const int x, const int y);

	// Voids
	void operator+=(const Ivec2& other);
	void operator-=(const Ivec2& other);
	void operator*=(const Ivec2& other);
	void operator/=(const Ivec2& other);
	void operator+=(const int& other);
	void operator-=(const int& other);
	void operator/=(const int& other);
	void operator*=(const int& other);

	// Vectors
	const Ivec2 operator-() const;
	const Ivec2 operator+(const Ivec2& other) const;
	const Ivec2 operator-(const Ivec2& other) const;
	const Ivec2 operator*(const Ivec2& other) const;
	const Ivec2 operator/(const Ivec2& other) const;
	const Ivec2 operator+(const int& other) const;
	const Ivec2 operator-(const int& other) const;
	const Ivec2 operator*(const int& other) const;
	const Ivec2 operator/(const int& other) const;

	// Booleans
	const bool operator==(const Ivec2& other) const;
	const bool operator!=(const Ivec2& other) const;

	// Miscellaneous
	union
	{
		int f[2];

		struct
		{
			int x;
			int y;
		};
	};
};