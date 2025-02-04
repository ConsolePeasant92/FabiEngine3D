#include "mathematics.hpp"

const fmat44 Mathematics::createTranslationMatrixX(float value)
{
	fmat44 result = {};

	result.m[3][0] = value;

	return result;
}

const fmat44 Mathematics::createTranslationMatrixY(float value)
{
	fmat44 result = {};

	result.m[3][1] = value;

	return result;
}

const fmat44 Mathematics::createTranslationMatrixZ(float value)
{
	fmat44 result = {};

	result.m[3][2] = value;

	return result;
}

const fmat44 Mathematics::createTranslationMatrix(float x, float y, float z)
{
	fmat44 result = {};

	result.m[3][0] = x;
	result.m[3][1] = y;
	result.m[3][2] = z;

	return result;
}

const fmat44 Mathematics::createScalingMatrix(float x, float y, float z)
{
	fmat44 result = {};

	result.m[0][0] = x;
	result.m[1][1] = y;
	result.m[2][2] = z;

	return result;
}

const fmat44 Mathematics::createScalingMatrixX(float value)
{
	fmat44 result = {};

	result.m[0][0] = value;

	return result;
}

const fmat44 Mathematics::createScalingMatrixY(float value)
{
	fmat44 result = {};

	result.m[1][1] = value;

	return result;
}

const fmat44 Mathematics::createScalingMatrixZ(float value)
{
	fmat44 result = {};

	result.m[2][2] = value;

	return result;
}

const fmat44 Mathematics::createRotationMatrix(float x, float y, float z, DirectionOrderType order)
{
	fmat44 result = {};

	switch(order)
	{
		case DirectionOrderType::XYZ:
		{
			result = (result * createRotationMatrixX(x));
			result = (result * createRotationMatrixY(y));
			result = (result * createRotationMatrixZ(z));

			break;
		}
		case DirectionOrderType::XZY:
		{
			result = (result * createRotationMatrixX(x));
			result = (result * createRotationMatrixZ(z));
			result = (result * createRotationMatrixY(y));

			break;
		}
		case DirectionOrderType::YXZ:
		{
			result = (result * createRotationMatrixY(y));
			result = (result * createRotationMatrixX(x));
			result = (result * createRotationMatrixZ(z));

			break;
		}
		case DirectionOrderType::YZX:
		{
			result = (result * createRotationMatrixY(y));
			result = (result * createRotationMatrixZ(z));
			result = (result * createRotationMatrixX(x));

			break;
		}
		case DirectionOrderType::ZXY:
		{
			result = (result * createRotationMatrixZ(z));
			result = (result * createRotationMatrixX(x));
			result = (result * createRotationMatrixY(y));

			break;
		}
		case DirectionOrderType::ZYX:
		{
			result = (result * createRotationMatrixZ(z));
			result = (result * createRotationMatrixY(y));
			result = (result * createRotationMatrixX(x));

			break;
		}
	}

	return result;
}

const fmat44 Mathematics::createRotationMatrixX(float angle)
{
	fmat44 result = {};

	result.m[1][1] = cos(angle);
	result.m[1][2] = sin(angle);
	result.m[2][1] = -sin(angle);
	result.m[2][2] = cos(angle);

	return result;
}

const fmat44 Mathematics::createRotationMatrixY(float angle)
{
	fmat44 result = {};

	result.m[0][0] = cos(angle);
	result.m[0][2] = -sin(angle);
	result.m[2][0] = sin(angle);
	result.m[2][2] = cos(angle);

	return result;
}

const fmat44 Mathematics::createRotationMatrixZ(float angle)
{
	fmat44 result = {};

	result.m[0][0] = cos(angle);
	result.m[1][0] = -sin(angle);
	result.m[0][1] = sin(angle);
	result.m[1][1] = cos(angle);

	return result;
}

const fmat44 Mathematics::createOrthographicProjectionMatrix(float leftX, float rightX, float bottomY, float topY, float nearZ, float farZ)
{
	fmat44 result = {};

	result.m[0][0] = (2.0f / (rightX - leftX));
	result.m[1][1] = (2.0f / (topY - bottomY));
	result.m[2][2] = (-2.0f / (farZ - nearZ));
	result.m[3][0] = -((rightX + leftX) / (rightX - leftX));
	result.m[3][1] = -((topY + bottomY) / (topY - bottomY));
	result.m[3][2] = -((farZ + nearZ) / (farZ - nearZ));

	return result;
};

const fmat44 Mathematics::createViewMatrix(const fvec3 & eye, const fvec3 & center, const fvec3 & up)
{
	const auto finalFront = normalize(center - eye);
	const auto finalRight = normalize(calculateCrossProduct(finalFront, up));
	const auto finalUp = calculateCrossProduct(finalRight, finalFront);

	fmat44 result = {};

	result.m[0][0] = finalRight.x;
	result.m[1][0] = finalRight.y;
	result.m[2][0] = finalRight.z;
	result.m[0][1] = finalUp.x;
	result.m[1][1] = finalUp.y;
	result.m[2][1] = finalUp.z;
	result.m[0][2] = -(finalFront.x);
	result.m[1][2] = -(finalFront.y);
	result.m[2][2] = -(finalFront.z);
	result.m[3][0] = -(calculateDotProduct(finalRight, eye));
	result.m[3][1] = -(calculateDotProduct(finalUp, eye));
	result.m[3][2] = calculateDotProduct(finalFront, eye);

	return result;
}

const fmat44 Mathematics::createPerspectiveProjectionMatrix(float fov, float aspect, float near, float far)
{
	const float tanHalfFovY = tan(fov * 0.5f);

	auto result = fmat44(0.0f);

	result.m[0][0] = (1.0f / (aspect * tanHalfFovY));
	result.m[1][1] = (1.0f / tanHalfFovY);
	result.m[2][2] = -((far + near) / (far - near));
	result.m[2][3] = -1.0f;
	result.m[3][2] = -((2.0f * far * near) / (far - near));

	return result;
}