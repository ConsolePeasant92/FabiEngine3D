#pragma once

#include "mathematics.hpp"
#include "animation3d_speed_type.hpp"
#include "transformation_type.hpp"

#include <map>
#include <string>

using std::map;
using std::string;

class Animation3dFrame final
{
public:
	void addPart(const string& partId, const fvec3& targetTransformation, const fvec3& rotationOrigin, const fvec3& speed, Animation3dSpeedType animationSpeedType, TransformationType transformationType);
	void deleteParts();
	void setTargetTransformation(const string& partId, const fvec3& value);
	void setRotationOrigin(const string& partId, const fvec3& value);
	void setSpeed(const string& partId, const fvec3& value);
	void setSpeedType(const string& partId, Animation3dSpeedType value);
	void setTransformationType(const string& partId, TransformationType value);

	const map<string, fvec3>& getTargetTransformations() const;
	const map<string, fvec3>& getRotationOrigins() const;
	const map<string, fvec3>& getSpeeds() const;

	const map<string, Animation3dSpeedType>& getSpeedTypes() const;
	const map<string, TransformationType>& getTransformationTypes() const;

private:
	map<string, fvec3> _targetTransformations;
	map<string, fvec3> _rotationOrigins;
	map<string, fvec3> _speeds;

	map<string, Animation3dSpeedType> _speedTypes;
	map<string, TransformationType> _transformationTypes;
};