#pragma once

#include "model_part.hpp"

#include <unordered_map>
#include <string>

using std::string;
using std::unique_ptr;
using std::unordered_map;

class Model final
{
public:
	Model(const string & id);

	void createPart(const string & partId);
	void deletePart(const string & partId);
	void deleteParts();
	void updateTarget();
	void updateTransformation();
	void setShadowed(bool value);
	void setReflected(bool value);
	void setRefracted(bool value);
	void setLevelOfDetailed(bool value);
	void setLevelOfDetailId(const string & value);
	void setPreviousCaptorId(const string & value);
	void setCurrentCaptorId(const string & value);
	void setCubeReflectionMixValue(float value);
	void setCubeRefractionMixValue(float value);
	void setMinClipPosition(const fvec3 & value);
	void setMaxClipPosition(const fvec3 & value);
	void setLevelOfDetailDistance(float value);
	void setBright(const string & partId, bool value);
	void setVertexBuffer(const string & partId, shared_ptr<VertexBuffer> value);
	void setDiffuseTextureBuffer(const string & partId, shared_ptr<TextureBuffer> value);
	void setEmissionTextureBuffer(const string & partId, shared_ptr<TextureBuffer> value);
	void setSpecularTextureBuffer(const string & partId, shared_ptr<TextureBuffer> value);
	void setReflectionTextureBuffer(const string & partId, shared_ptr<TextureBuffer> value);
	void setRefractionTextureBuffer(const string & partId, shared_ptr<TextureBuffer> value);
	void setNormalTextureBuffer(const string & partId, shared_ptr<TextureBuffer> value);
	void setBasePosition(const fvec3 & value);
	void setBaseRotation(const fvec3 & value);
	void setBaseRotationOrigin(const fvec3 & value);
	void setBaseSize(const fvec3 & value);
	void setPartPosition(const string & partId, const fvec3 & value);
	void setPartRotation(const string & partId, const fvec3 & value);
	void setPartRotationOrigin(const string & partId, const fvec3 & value);
	void setPartSize(const string & partId, const fvec3 & value);
	void moveBase(const fvec3 & value);
	void rotateBase(const fvec3 & value);
	void scaleBase(const fvec3 & value);
	void movePart(const string & partId, const fvec3 & value);
	void rotatePart(const string & partId, const fvec3 & value);
	void scalePart(const string & partId, const fvec3 & value);
	void moveBaseTo(const fvec3 & target, float speed);
	void rotateBaseTo(const fvec3 & target, float speed);
	void scaleBaseTo(const fvec3 & target, float speed);
	void movePartTo(const string & partId, const fvec3 & target, float speed);
	void rotatePartTo(const string & partId, const fvec3 & target, float speed);
	void scalePartTo(const string & partId, const fvec3 & target, float speed);
	void setColor(const string & partId, const fvec3 & value);
	void setWireframeColor(const string & partId, const fvec3 & value);
	void setMeshPath(const string & value);
	void setDiffuseMapPath(const string & partId, const string & value);
	void setEmissionMapPath(const string & partId, const string & value);
	void setSpecularMapPath(const string & partId, const string & value);
	void setReflectionMapPath(const string & partId, const string & value);
	void setRefractionMapPath(const string & partId, const string & value);
	void setNormalMapPath(const string & partId, const string & value);
	void setReflectivity(const string & partId, float value);
	void setRefractivity(const string & partId, float value);
	void setLightness(const string & partId, float value);
	void setSpecularShininess(const string & partId, float value);
	void setSpecularIntensity(const string & partId, float value);
	void setOpacity(const string & partId, float value);
	void setTextureRepeat(const string & partId, int value);
	void setEmissionIntensity(const string & partId, float value);
	void setSpecular(const string & partId, bool value);
	void setReflective(const string & partId, bool value);
	void setRefractive(const string & partId, bool value);
	void setReflectionType(const string & partId, ReflectionType value);
	void setRefractionType(const string & partId, RefractionType value);
	void setWireframed(const string & partId, bool value);
	void setFaceCulled(const string & partId, bool value);
	void setRotationOrder(DirectionOrderType value);
	void setMinAlpha(const string & partId, float value);
	void setVisible(bool value);

	const vector<string> getPartIds() const;

	const shared_ptr<VertexBuffer> getVertexBuffer(const string & partId) const;
	const shared_ptr<TextureBuffer> getDiffuseTextureBuffer(const string & partId) const;
	const shared_ptr<TextureBuffer> getEmissionTextureBuffer(const string & partId) const;
	const shared_ptr<TextureBuffer> getSpecularTextureBuffer(const string & partId) const;
	const shared_ptr<TextureBuffer> getReflectionTextureBuffer(const string & partId) const;
	const shared_ptr<TextureBuffer> getRefractionTextureBuffer(const string & partId) const;
	const shared_ptr<TextureBuffer> getNormalTextureBuffer(const string & partId) const;

	const string & getId() const;
	const string & getMeshPath() const;
	const string & getLevelOfDetailId() const;
	const string & getPreviousCaptorId() const;
	const string & getCurrentCaptorId() const;
	const string & getDiffuseMapPath(const string & partId) const;
	const string & getEmissionMapPath(const string & partId) const;
	const string & getSpecularMapPath(const string & partId) const;
	const string & getReflectionMapPath(const string & partId) const;
	const string & getRefractionMapPath(const string & partId) const;
	const string & getNormalMapPath(const string & partId) const;

	const fmat44 & getTransformation(const string & partId) const;

	const fvec3 & getColor(const string & partId) const;
	const fvec3 & getWireframeColor(const string & partId) const;
	const fvec3 & getBasePosition() const;
	const fvec3 & getBaseRotation() const;
	const fvec3 & getBaseRotationOrigin() const;
	const fvec3 & getBaseSize() const;
	const fvec3 & getPartPosition(const string & partId) const;
	const fvec3 & getPartRotation(const string & partId) const;
	const fvec3 & getPartRotationOrigin(const string & partId) const;
	const fvec3 & getPartSize(const string & partId) const;
	const fvec3 & getMinClipPosition() const;
	const fvec3 & getMaxClipPosition() const;

	const float getCubeReflectionMixValue() const;
	const float getCubeRefractionMixValue() const;
	const float getLevelOfDetailDistance() const;
	const float getReflectivity(const string & partId) const;
	const float getRefractivity(const string & partId) const;
	const float getLightness(const string & partId) const;
	const float getSpecularShininess(const string & partId) const;
	const float getSpecularIntensity(const string & partId) const;
	const float getOpacity(const string & partId) const;
	const float getEmissionIntensity(const string & partId) const;
	const float getMinAlpha(const string & partId) const;

	const int getTextureRepeat(const string & partId) const;

	const bool isVisible() const;
	const bool isLevelOfDetailed() const;
	const bool isShadowed() const;
	const bool isReflected() const;
	const bool isRefracted() const;
	const bool isBright(const string & partId) const;
	const bool isFaceCulled(const string & partId) const;
	const bool isWireframed(const string & partId) const;
	const bool isSpecular(const string & partId) const;
	const bool isReflective(const string & partId) const;
	const bool isRefractive(const string & partId) const;

	const ReflectionType getReflectionType(const string & partId) const;
	const RefractionType getRefractionType(const string & partId) const;
	const DirectionOrderType getRotationOrder() const;

private:
	void _correctPositionTarget(fvec3 & current, const fvec3 & target, float speed);
	void _correctRotationTarget(fvec3 & current, const fvec3 & target, float speed);
	void _correctSizeTarget(fvec3 & current, const fvec3 & target, float speed);

	const string _id;

	unordered_map<string, unique_ptr<ModelPart>> _parts = {};

	string _meshPath = "";
	string _levelOfDetailId = "";
	string _previousCaptorId = "";
	string _currentCaptorId = "";

	fvec3 _basePosition = fvec3(0.0f);
	fvec3 _baseRotation = fvec3(0.0f);
	fvec3 _baseRotationOrigin = fvec3(0.0f);
	fvec3 _baseSize = fvec3(1.0f);
	fvec3 _basePositionTarget = fvec3(0.0f);
	fvec3 _baseRotationTarget = fvec3(0.0f);
	fvec3 _baseSizeTarget = fvec3(1.0f);
	fvec3 _minClipPosition = fvec3(-FLT_MAX);
	fvec3 _maxClipPosition = fvec3(FLT_MAX);

	float _basePositionTargetSpeed = 0.0f;
	float _baseRotationTargetSpeed = 0.0f;
	float _baseSizeTargetSpeed = 0.0f;
	float _cubeReflectionMixValue = 1.0f;
	float _cubeRefractionMixValue = 1.0f;
	float _levelOfDetailDistance = 0.0f;

	bool _isShadowed = true;
	bool _isReflected = true;
	bool _isRefracted = true;
	bool _isLevelOfDetailed = false;
	bool _isVisible = true;

	DirectionOrderType _rotationOrder = DirectionOrderType::YXZ;
};