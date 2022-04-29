#pragma once

#include "base_entity.hpp"
#include "vertex_buffer.hpp"
#include "direction_type.hpp"
#include "aabb_parent_type.hpp"

#include <memory>

using std::shared_ptr;

class Aabb final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	void setVertexBuffer(shared_ptr<VertexBuffer> value);
	void updateTarget();
	void updateTransformation();
	void setLocalPosition(const fvec3 & value);
	void setLocalSize(const fvec3 & value);
	void setBasePosition(const fvec3 & value);
	void setBaseSize(const fvec3 & value);
	void moveBase(const fvec3 & value);
	void scaleBase(const fvec3 & value);
	void moveBaseTo(const fvec3 & target, float speed);
	void scaleBaseTo(const fvec3 & target, float speed);
	void moveLocal(const fvec3 & value);
	void scaleLocal(const fvec3 & value);
	void moveLocalTo(const fvec3 & target, float speed);
	void scaleLocalTo(const fvec3 & target, float speed);
	void setParentId(const string & value);
	void setParentType(AabbParentType value);
	void setCollisionDirection(DirectionType value);
	void setRaycastResponsive(bool value);
	void setCollisionResponsive(bool value);
	void setCollided(bool value);
	void setColor(const fvec3 & value);
	void setCentered(bool value);
	void setMinClipPosition(const fvec3 & value);
	void setMaxClipPosition(const fvec3 & value);

	const shared_ptr<VertexBuffer> getVertexBuffer() const;

	const string & getParentId() const;

	const mat44 & getTransformation() const;

	const fvec3 & getLocalPosition() const;
	const fvec3 & getLocalSize() const;
	const fvec3 & getBasePosition() const;
	const fvec3 & getBaseSize() const;
	const fvec3 & getColor() const;
	const fvec3 & getMinClipPosition() const;
	const fvec3 & getMaxClipPosition() const;

	const bool isCentered() const;
	const bool isRaycastResponsive() const;
	const bool isCollisionResponsive() const;
	const bool hasParent() const;
	const bool hasCollided() const;

	const AabbParentType getParentType() const;
	const DirectionType getCollisionDirection() const;

private:
	shared_ptr<VertexBuffer> _vertexBuffer = nullptr;

	string _parentId = "";

	mat44 _transformation = mat44(1.0f);

	fvec3 _basePosition = fvec3(0.0f);
	fvec3 _baseSize = fvec3(1.0f);
	fvec3 _basePositionTarget = fvec3(0.0f);
	fvec3 _baseSizeTarget = fvec3(1.0f);
	fvec3 _localPosition = fvec3(0.0f);
	fvec3 _localSize = fvec3(1.0f);
	fvec3 _localPositionTarget = fvec3(0.0f);
	fvec3 _localSizeTarget = fvec3(1.0f);
	fvec3 _color = fvec3(1.0f);
	fvec3 _minClipPosition = fvec3(-FLT_MAX);
	fvec3 _maxClipPosition = fvec3(FLT_MAX);

	float _basePositionTargetSpeed = 0.0f;
	float _baseSizeTargetSpeed = 0.0f;
	float _localPositionTargetSpeed = 0.0f;
	float _localSizeTargetSpeed = 0.0f;

	bool _isCentered = false;
	bool _isRaycastResponsive = true;
	bool _isCollisionResponsive = true;
	bool _hasCollided = false;

	AabbParentType _parentType = {};
	DirectionType _collisionDirection = {};
};