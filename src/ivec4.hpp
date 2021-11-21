#pragma once

struct ivec2;
struct ivec3;
struct ivec4;
struct fvec2;
struct fvec3;
struct fvec4;

struct ivec4 final
{
	ivec4();
	ivec4(const ivec2& other);
	ivec4(const ivec3& other);
	ivec4(const ivec4& other);
	ivec4(const fvec2& other);
	ivec4(const fvec3& other);
	ivec4(const fvec4& other);
	ivec4(const int& value);
	ivec4(const int& x, const int& y, const int& z, const int& w);

	// Voids
	void operator+=(const ivec4& other);
	void operator-=(const ivec4& other);
	void operator*=(const ivec4& other);
	void operator/=(const ivec4& other);
	void operator+=(const int& other);
	void operator-=(const int& other);
	void operator/=(const int& other);
	void operator*=(const int& other);

	// Vectors
	const ivec4 operator-() const;
	const ivec4 operator+(const ivec4& other) const;
	const ivec4 operator-(const ivec4& other) const;
	const ivec4 operator*(const ivec4& other) const;
	const ivec4 operator/(const ivec4& other) const;
	const ivec4 operator+(const int& other) const;
	const ivec4 operator-(const int& other) const;
	const ivec4 operator*(const int& other) const;
	const ivec4 operator/(const int& other) const;

	// Booleans
	const bool operator==(const ivec4& other) const;
	const bool operator!=(const ivec4& other) const;

	// Miscellaneous
	union
	{
		int f[4];

		struct
		{
			int x;
			int y;
			int z;
			int w;
		};
	};
};