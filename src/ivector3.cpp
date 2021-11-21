#include "ivector3.hpp"
#include "vector3.hpp"

ivec3::ivec3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

ivec3::ivec3(const fvec3& other)
{
	this->x = static_cast<int>(other.x);
	this->y = static_cast<int>(other.y);
	this->z = static_cast<int>(other.z);
}

ivec3::ivec3(const int value)
{
	this->x = value;
	this->y = value;
	this->z = value;
}

ivec3::ivec3(const int x, const int y, const int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void ivec3::operator+=(const ivec3& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}

void ivec3::operator-=(const ivec3& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}

void ivec3::operator*=(const ivec3& v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
}

void ivec3::operator/=(const ivec3& v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
}

void ivec3::operator+=(const int& value)
{
	this->x += value;
	this->y += value;
	this->z += value;
}

void ivec3::operator-=(const int& value)
{
	this->x -= value;
	this->y -= value;
	this->z -= value;
}

void ivec3::operator/=(const int& value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;
}

void ivec3::operator*=(const int& value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
}

const ivec3 ivec3::operator-() const
{
	return ivec3(-this->x, -this->y, -this->z);
}

const ivec3 ivec3::operator+(const ivec3& other) const
{
	return ivec3((this->x + other.x), (this->y + other.y), (this->z + other.z));
}

const ivec3 ivec3::operator-(const ivec3& other) const
{
	return ivec3((this->x - other.x), (this->y - other.y), (this->z - other.z));
}

const ivec3 ivec3::operator*(const ivec3& other) const
{
	return ivec3((this->x * other.x), (this->y * other.y), (this->z * other.z));
}

const ivec3 ivec3::operator/(const ivec3& other) const
{
	return ivec3((this->x / other.x), (this->y / other.y), (this->z / other.z));
}

const ivec3 ivec3::operator+(const int& other) const
{
	return ivec3((this->x + other), (this->y + other), (this->z + other));
}

const ivec3 ivec3::operator-(const int& other) const
{
	return ivec3((this->x - other), (this->y - other), (this->z - other));
}

const ivec3 ivec3::operator*(const int& other) const
{
	return ivec3((this->x * other), (this->y * other), (this->z * other));
}

const ivec3 ivec3::operator/(const int& other) const
{
	return ivec3((this->x / other), (this->y / other), (this->z / other));
}

const bool ivec3::operator==(const ivec3& other) const
{
	return ((this->x == other.x) && (this->y == other.y) && (this->z == other.z));
}

const bool ivec3::operator!=(const ivec3& other) const
{
	return ((this->x != other.x) || (this->y != other.y) || (this->z != other.z));
}