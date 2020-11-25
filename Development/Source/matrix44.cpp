#include "matrix44.hpp"
#include "matrix33.hpp"

// Create the matrix with specified values
Matrix44::Matrix44(
	float m00, float m01, float m02, float m03, 
	float m10, float m11, float m12, float m13, 
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	this->m[0][0] = m00; this->m[1][0] = m10; this->m[2][0] = m20; this->m[3][0] = m30;
	this->m[0][1] = m01; this->m[1][1] = m11; this->m[2][1] = m21; this->m[3][1] = m31;
	this->m[0][2] = m02; this->m[1][2] = m12; this->m[2][2] = m22; this->m[3][2] = m32;
	this->m[0][3] = m03; this->m[1][3] = m13; this->m[2][3] = m23; this->m[3][3] = m33;
}

float Matrix44::operator[](unsigned int index) const
{
	return this->f[index];
}

// Create the identity matrix
Matrix44::Matrix44()
{
	for (int i = 0; i < 16; i++) {
		f[i] = 0.0f;
	}

	this->m[0][0] = 1.0f;
	this->m[1][1] = 1.0f;
	this->m[2][2] = 1.0f;
	this->m[3][3] = 1.0f;
}

// Create a custom identity matrix
Matrix44::Matrix44(float value)
{
	for (int i = 0; i < 16; i++) {
		f[i] = 0.0f;
	}

	this->m[0][0] = value;
	this->m[1][1] = value;
	this->m[2][2] = value;
	this->m[3][3] = value;
}

// Create a matrix from another smaller matrix
Matrix44::Matrix44(const Matrix33& other)
{
	this->m[0][0] = other.m[0][0]; this->m[1][0] = other.m[1][0]; this->m[2][0] = other.m[2][0]; this->m[3][0] = 0.0f;
	this->m[0][1] = other.m[0][1]; this->m[1][1] = other.m[1][1]; this->m[2][1] = other.m[2][1]; this->m[3][1] = 0.0f;
	this->m[0][2] = other.m[0][2]; this->m[1][2] = other.m[1][2]; this->m[2][2] = other.m[2][2]; this->m[3][2] = 0.0f;
	this->m[0][3] = 0.0f; this->m[1][3] = 0.0f; this->m[2][3] = 0.0f; this->m[3][3] = 1.0f;
}

// Matrix-vector3 multiplication
Vec3 Matrix44::operator*(const Vec3& other) const
{
	Vec3 newVector;

	newVector.x = this->m[0][0] * other.x + this->m[1][0] * other.y + this->m[2][0] * other.z + this->m[3][0] * 1.0f;
	newVector.y = this->m[0][1] * other.x + this->m[1][1] * other.y + this->m[2][1] * other.z + this->m[3][1] * 1.0f;
	newVector.z = this->m[0][2] * other.x + this->m[1][2] * other.y + this->m[2][2] * other.z + this->m[3][2] * 1.0f;

	return newVector;

}

// Matrix-vector4 multiplication
Vec4 Matrix44::operator*(const Vec4& other) const
{
	Vec4 newVector;

	newVector.x = this->m[0][0] * other.x + this->m[1][0] * other.y + this->m[2][0] * other.z + this->m[3][0] * other.w;
	newVector.y = this->m[0][1] * other.x + this->m[1][1] * other.y + this->m[2][1] * other.z + this->m[3][1] * other.w;
	newVector.z = this->m[0][2] * other.x + this->m[1][2] * other.y + this->m[2][2] * other.z + this->m[3][2] * other.w;
	newVector.w = this->m[0][3] * other.x + this->m[1][3] * other.y + this->m[2][3] * other.z + this->m[3][3] * other.w;

	return newVector;

}

// Matrix-matrix addition
Matrix44 Matrix44::operator+(const Matrix44& other) const
{
	Matrix44 newMatrix;

	for (int i = 0; i < 16; i++) {
		newMatrix.f[i] = this->f[i] + other.f[i];
	}

	return newMatrix;
}

// Matrix-matrix subtraction
Matrix44 Matrix44::operator-(const Matrix44& other) const
{
	Matrix44 newMatrix;

	for (int i = 0; i < 16; i++) {
		newMatrix.f[i] = this->f[i] - other.f[i];
	}

	return newMatrix;
}

// Matrix-matrix multiplication
Matrix44 Matrix44::operator*(const Matrix44& other) const
{
	Matrix44 newMatrix(0.0f);

	for (int column = 0; column < 4; column++) {
		for (int row = 0; row < 4; row++) {
			for (int inner = 0; inner < 4; inner++) {
				newMatrix.m[row][column] += this->m[inner][column] * other.m[row][inner];
			}
		}
	}

	return newMatrix;
}

// Return X axis of the matrix
Vec3 Matrix44::GetXAxis() const
{
	Vec3 newVector;
	newVector.x = this->m[0][0];
	newVector.y = this->m[0][1];
	newVector.z = this->m[0][2];

	return newVector;
}

// Return Y axis of the matrix
Vec3 Matrix44::GetYAxis() const
{
	Vec3 newVector;

	newVector.x = this->m[1][0];
	newVector.y = this->m[1][1];
	newVector.z = this->m[1][2];

	return newVector;
}

// Return Z axis of the matrix
Vec3 Matrix44::GetZAxis() const
{
	Vec3 newVector;

	newVector.x = this->m[2][0];
	newVector.y = this->m[2][1];
	newVector.z = this->m[2][2];

	return newVector;
}

// Set the euler axis of the matrix
void Matrix44::SetEulerAxis(float yaw, float pitch, float roll)
{
	Matrix44 newMatrix;

	Matrix44 yawMatrix = createRotationY(yaw);
	Matrix44 pitchMatrix = createRotationX(pitch);
	Matrix44 rollMatrix = createRotationZ(roll);
	newMatrix = yawMatrix * pitchMatrix * rollMatrix;

	*this = newMatrix;
}