#pragma once

#include <cmath>

struct ivec3;

struct fvec3 final
{
	fvec3();
	fvec3(const ivec3& other);
	fvec3(const float value);
	fvec3(const float x, const float y, const float z);

	// Voids
	void operator+=(const float& other);
	void operator-=(const float& other);
	void operator*=(const float& other);
	void operator/=(const float& other);
	void operator+=(const fvec3& other);
	void operator-=(const fvec3& other);
	void operator*=(const fvec3& other);
	void operator/=(const fvec3& other);

	// Vectors
	const fvec3 operator+(const fvec3& other) const;
	const fvec3 operator-(const fvec3& other) const;
	const fvec3 operator*(const fvec3& other) const;
	const fvec3 operator/(const fvec3& other) const;
	const fvec3 operator+(const float& other) const;
	const fvec3 operator-(const float& other) const;
	const fvec3 operator*(const float& other) const;
	const fvec3 operator/(const float& other) const;
	const fvec3 operator-() const;

	// Booleans
	const bool operator==(const fvec3& other) const;
	const bool operator!=(const fvec3& other) const;

	// Miscellaneous
	union
	{
		float f[3];

		struct
		{
			float x;
			float y;
			float z;
		};

		struct
		{
			float r;
			float g;
			float b;
		};
	};
};