#pragma once

#include "base_entity.hpp"
#include "render_buffer.hpp"
#include "reflection_type.hpp"

#include <memory>

using std::shared_ptr;
using std::numeric_limits;

class ModelEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// Voids
	void createPart(const string& ID);
	void updateTransformation();
	void updateTransformationMatrix();
	void setRenderBuffer(const string& partID, shared_ptr<RenderBuffer> value);
	void setDiffuseMap(const string& partID, TextureID value);
	void setEmissionMap(const string& partID, TextureID value);
	void setReflectionMap(const string& partID, TextureID value);
	void setNormalMap(const string& partID, TextureID value);
	void setPosition(const string& partID, Vec3 value);
	void setRotation(const string& partID, Vec3 value);
	void setRotationOrigin(const string& partID, Vec3 value);
	void setSize(const string& partID, Vec3 value);
	void move(const string& partID, Vec3 value);
	void rotate(const string& partID, Vec3 value);
	void scale(const string& partID, Vec3 value);
	void moveTo(const string& partID, Vec3 target, float speed);
	void rotateTo(const string& partID, Vec3 target, float speed);
	void scaleTo(const string& partID, Vec3 target, float speed);
	void setColor(const string& partID, Vec3 value);
	void setInversion(const string& partID, float value);
	void setDiffuseMapPath(const string& partID, const string& value);
	void setEmissionMapPath(const string& partID, const string& value);
	void setReflectionMapPath(const string& partID, const string& value);
	void setNormalMapPath(const string& partID, const string& value);
	void setLevelOfDetailSize(Vec3 value);
	void setLevelOfDetailEntityID(const string& value);
	void setMeshPath(const string& value);
	void setPreviousReflectionEntityID(const string& value);
	void setCurrentReflectionEntityID(const string& value);
	void setCubeReflectionMixValue(float value);
	void setReflectivity(float value);
	void setLightness(float value);
	void setSpecularFactor(float value);
	void setSpecularIntensity(float value);
	void setMinHeight(float value);
	void setMaxHeight(float value);
	void setAlpha(float value);
	void setUvRepeat(float value);
	void setTransparent(bool value);
	void setFaceCulled(bool value);
	void setSpecularLighted(bool value);
	void setShadowed(bool value);
	void setReflected(bool value);
	void setCameraStatic(bool value);
	void setDepthMapIncluded(bool value);
	void setLevelOfDetailed(bool value);
	void setWireFramed(bool value);
	void setBright(bool value);
	void setReflectionType(ReflectionType value);
	void clearParts();

	// Instances
	const shared_ptr<RenderBuffer> getRenderBuffer(const string& partID);

	// Strings
	const vector<string> getPartIDs();
	const string& getMeshPath();
	const string& getDiffuseMapPath(const string& partID);
	const string& getEmissionMapPath(const string& partID);
	const string& getReflectionMapPath(const string& partID);
	const string& getNormalMapPath(const string& partID);
	const string& getLevelOfDetailEntityID();
	const string& getPreviousReflectionEntityID();
	const string& getCurrentReflectionEntityID();

	// Matrices
	const Matrix44& getTransformationMatrix(const string& partID);

	// Vectors
	const Vec3 getPosition(const string& partID);
	const Vec3 getRotation(const string& partID);
	const Vec3 getRotationOrigin(const string& partID);
	const Vec3 getSize(const string& partID);
	const Vec3 getColor(const string& partID);
	const Vec3 getLevelOfDetailSize();

	// Floats
	const float getInversion(const string& partID);
	const float getCubeReflectionMixValue();
	const float getReflectivity();
	const float getLightness();
	const float getSpecularFactor();
	const float getSpecularIntensity();
	const float getAlpha();
	const float getUvRepeat();
	const float getMinHeight();
	const float getMaxHeight();

	// Booleans
	const bool isTransparent();
	const bool isFaceCulled();
	const bool isSpecularLighted();
	const bool isShadowed();
	const bool isReflected();
	const bool isCameraStatic();
	const bool isDepthMapIncluded();
	const bool isLevelOfDetailed();
	const bool isWireFramed();
	const bool isBright();
	const bool hasRenderBuffer(const string& partID);
	const bool hasDiffuseMap(const string& partID);
	const bool hasEmissionMap(const string& partID);
	const bool hasReflectionMap(const string& partID);
	const bool hasNormalMap(const string& partID);

	// Miscellaneous
	const TextureID getDiffuseMap(const string& partID);
	const TextureID getEmissionMap(const string& partID);
	const TextureID getReflectionMap(const string& partID);
	const TextureID getNormalMap(const string& partID);
	const ReflectionType getReflectionType();

private:
	struct PartData final
	{
		PartData(const string& ID)
			:
			ID(ID)
		{

		}

		// Instances
		shared_ptr<RenderBuffer> renderBuffer = nullptr;

		// Strings
		const string ID;
		string diffuseMapPath = "";
		string emissionMapPath = "";
		string reflectionMapPath = "";
		string normalMapPath = "";

		// Matrices
		Matrix44 transformationMatrix = Matrix44(1.0f);

		// Vectors
		Vec3 localPosition = Vec3(0.0f);
		Vec3 localRotation = Vec3(0.0f);
		Vec3 localRotationOrigin = Vec3(0.0f);
		Vec3 localSize = Vec3(1.0f);
		Vec3 localPositionTarget = Vec3(0.0f);
		Vec3 localRotationTarget = Vec3(0.0f);
		Vec3 localSizeTarget = Vec3(1.0f);
		Vec3 color = Vec3(1.0f);

		// Floats
		float localPositionTargetSpeed = 0.0f;
		float localRotationTargetSpeed = 0.0f;
		float localSizeTargetSpeed = 0.0f;
		float inversion = 0.0f;

		// Miscellaneous
		TextureID diffuseMap = 0;
		TextureID emissionMap = 0;
		TextureID reflectionMap = 0;
		TextureID normalMap = 0;
	};

	// Voids
	void _correctPositionTarget(Vec3& current, Vec3 target, float speed);
	void _correctRotationTarget(Vec3& current, Vec3 target, float speed);
	void _correctSizeTarget(Vec3& current, Vec3 target, float speed);

	// Integers
	unsigned int _getPartIndex(const string& partID);

	// Instances
	vector<PartData> _parts;

	// Strings
	string _meshPath = "";
	string _levelOfDetailEntityID = "";
	string _previousReflectionEntityID = "";
	string _currentReflectionEntityID = "";

	// Vectors
	Vec3 _basePosition = Vec3(0.0f);
	Vec3 _baseRotation = Vec3(0.0f);
	Vec3 _baseRotationOrigin = Vec3(0.0f);
	Vec3 _baseSize = Vec3(1.0f);
	Vec3 _basePositionTarget = Vec3(0.0f);
	Vec3 _baseRotationTarget = Vec3(0.0f);
	Vec3 _baseSizeTarget = Vec3(1.0f);
	Vec3 _levelOfDetailSize = Vec3(1.0f);

	// Floats
	float _basePositionTargetSpeed = 0.0f;
	float _baseRotationTargetSpeed = 0.0f;
	float _baseSizeTargetSpeed = 0.0f;
	float _cubeReflectionMixValue = 1.0f;
	float _reflectivity = 0.5f;
	float _lightness = 1.0f;
	float _specularFactor = 1.0f;
	float _specularIntensity = 1.0f;
	float _alpha = 1.0f;
	float _uvRepeat = 1.0f;
	float _minHeight = -(numeric_limits<float>::max)();
	float _maxHeight = (numeric_limits<float>::max)();

	// Booleans
	bool _isCameraStatic = false;
	bool _isTransparent = false;
	bool _isFaceCulled = false;
	bool _isSpecularLighted = false;
	bool _isShadowed = true;
	bool _isReflected = true;
	bool _isDepthMapIncluded = true;
	bool _isLevelOfDetailed = false;
	bool _wireFramed = false;
	bool _isBright = false;

	// Miscellaneous
	ReflectionType _reflectionType;
};