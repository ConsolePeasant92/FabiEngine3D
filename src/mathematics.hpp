#pragma once

#include "ivector2.hpp"
#include "ivector3.hpp"
#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"
#include "matrix33.hpp"
#include "matrix44.hpp"
#include "direction_order.hpp"

#include <vector>
#include <random>
#include <ctime>

using std::vector;
using std::mt19937;

class Math final
{
public:
	Math() = delete;

	// Matrices
	static const mat33 invertMatrix(mat33 matrix);
	static const mat44 invertMatrix(mat44 matrix);
	static const mat33 transposeMatrix(mat33 matrix);
	static const mat44 transposeMatrix(mat44 matrix);
	static const mat44 createTranslationMatrix(float x, float y, float z);
	static const mat44 createTranslationMatrixX(float value);
	static const mat44 createTranslationMatrixY(float value);
	static const mat44 createTranslationMatrixZ(float value);
	static const mat44 createRotationMatrix(float x, float y, float z, DirectionOrder order);
	static const mat44 createRotationMatrixX(float angle);
	static const mat44 createRotationMatrixY(float angle);
	static const mat44 createRotationMatrixZ(float angle);
	static const mat44 createScalingMatrix(float x, float y, float z);
	static const mat44 createScalingMatrixX(float value);
	static const mat44 createScalingMatrixY(float value);
	static const mat44 createScalingMatrixZ(float value);
	static const mat44 createOrthoMatrix(float left, float right, float bottom, float top, float near, float far);
	static const mat44 createViewMatrix(fvec3 eye, fvec3 center, fvec3 up);
	static const mat44 createProjectionMatrix(float fov, float aspect, float near, float far);

	// Vectors
	static const fvec2 calculateAverage(const vector<fvec2>& values);
	static const fvec3 calculateAverage(const vector<fvec3>& values);
	static const fvec4 calculateAverage(const vector<fvec4>& values);
	static const fvec3 calculateCrossProduct(fvec3 firstVector, fvec3 secondVector);
	static const fvec2 calculateDifference(fvec2 firstPosition, fvec2 secondPosition);
	static const fvec3 calculateDifference(fvec3 firstPosition, fvec3 secondPosition);
	static const fvec4 calculateDifference(fvec4 firstPosition, fvec4 secondPosition);
	static const fvec2 normalize(fvec2 vector);
	static const fvec3 normalize(fvec3 vector);
	static const fvec4 normalize(fvec4 vector);
	static const fvec2 convertFromNDC(fvec2 position);
	static const fvec2 convertToNDC(fvec2 position);

	// Decimals
	static const float calculateDeterminant(mat33 matrix);
	static const float calculateDeterminant(mat44 matrix);
	static const float calculateDistance(fvec2 firstPosition, fvec2 secondPosition);
	static const float calculateDistance(fvec3 firstPosition, fvec3 secondPosition);
	static const float calculateDistance(fvec4 firstPosition, fvec4 secondPosition);
	static const float calculateDotProduct(fvec2 firstVector, fvec2 secondVector);
	static const float calculateDotProduct(fvec3 firstVector, fvec3 secondVector);
	static const float calculateDotProduct(fvec4 firstVector, fvec4 secondVector);
	static const float calculateMagnitude(fvec2 vector);
	static const float calculateMagnitude(fvec3 vector);
	static const float calculateMagnitude(fvec4 vector);
	static const float calculateAngleDifference(float firstAngle, float secondAngle);
	static const float calculateReferenceAngle(float angle);
	static const float calculateAverage(const vector<float>& values);
	static const float limitAngle(float angle);
	static const float convertToRadians(float degrees);
	static const float convertToDegrees(float radians);
	static const float getPI();
	static const float getRandomFloat(float min, float max);

	// Integers
	static const int calculateAverage(const vector<int>& values);
	static const int getRandomInteger(int min, int max);

	// Booleans
	static const bool isNormalized(fvec2 vector);
	static const bool isNormalized(fvec3 vector);
	static const bool isNormalized(fvec4 vector);

private:
	// Decimals
	static inline const float PI = 3.14159265358979323846264338327f;
	static inline const float DEG2RAD = 0.01745329251994329576923690768489f;
	static inline const float RAD2DEG = 57.295779513082320876798154814278f;

	// Miscellaneous
	static inline mt19937 _generator = mt19937(static_cast<unsigned int>(time(nullptr)));
};