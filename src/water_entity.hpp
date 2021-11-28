#pragma once

#include "base_entity.hpp"
#include "render_buffer.hpp"
#include "water_quality.hpp"

#include <memory>

using std::shared_ptr;

class WaterEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// VOID
	void setLowQualityRenderBuffer(shared_ptr<RenderBuffer> value);
	void setHighQualityRenderBuffer(shared_ptr<RenderBuffer> value);
	void setQuality(WaterQuality value);
	void setSpeed(fvec2 value);
	void setRippleOffset(fvec2 value);
	void setWaveOffset(fvec2 value);
	void setColor(fvec3 value);
	void setDudvMap(TextureID value);
	void setNormalMap(TextureID value);
	void setDisplacementMap(TextureID value);
	void setDudvMapPath(const string& value);
	void setNormalMapPath(const string& value);
	void setDisplacementMapPath(const string& value);
	void setTextureRepeat(float value);
	void setWaveHeight(float value);
	void setSpecularShininess(float value);
	void setSpecularIntensity(float value);
	void setHeight(float value);
	void setSize(float value);
	void setTransparency(float value);
	void setSpecular(bool value);
	void setReflective(bool value);
	void setRefractive(bool value);
	void setWireframed(bool value);
	void setWireframeColor(fvec3 value);

	// STRING
	const string& getDudvMapPath() const;
	const string& getNormalMapPath() const;
	const string& getDisplacementMapPath() const;

	// FVEC3
	const fvec3 getColor() const;
	const fvec3 getWireframeColor() const;

	// FVEC2
	const fvec2 getSpeed() const;
	const fvec2 getRippleOffset() const;
	const fvec2 getWaveOffset() const;

	// FLOAT
	const float getHeight() const;
	const float getTextureRepeat() const;
	const float getWaveHeight() const;
	const float getSpecularShininess() const;
	const float getSpecularIntensity() const;
	const float getSize() const;
	const float getTransparency() const;

	// BOOL
	const bool isSpecular() const;
	const bool isReflective() const;
	const bool isRefractive() const;
	const bool isWireframed() const;
	const bool hasLowQualityRenderBuffer() const;
	const bool hasHighQualityRenderBuffer() const;
	const bool hasDudvMap() const;
	const bool hasNormalMap() const;
	const bool hasDisplacementMap() const;

	// MISCELLANEOUS
	const shared_ptr<RenderBuffer> getLowQualityRenderBuffer() const;
	const shared_ptr<RenderBuffer> getHighQualityRenderBuffer() const;
	const WaterQuality getQuality() const;
	const TextureID getDudvMap() const;
	const TextureID getNormalMap() const;
	const TextureID getDisplacementMap() const;

private:
	// STRING
	string _dudvMapPath = "";
	string _normalMapPath = "";
	string _displacementMapPath = "";

	// FVEC3
	fvec3 _color = fvec3(1.0f);
	fvec3 _wireframeColor = fvec3(1.0f);

	// FVEC2
	fvec2 _speed = fvec2(0.0f);
	fvec2 _rippleOffset = fvec2(0.0f);
	fvec2 _waveOffset = fvec2(0.0f);

	// FLOAT
	float _height = 0.0f;
	float _size = 1.0f;
	float _textureRepeat = 1.0f;
	float _waveHeight = 0.0f;
	float _specularShininess = 1.0f;
	float _specularIntensity = 1.0f;
	float _transparency = 0.0f;

	// BOOL
	bool _isSpecular = false;
	bool _isReflective = false;
	bool _isRefractive = false;
	bool _isWireframed = false;

	// MISCELLANEOUS
	shared_ptr<RenderBuffer> _lowQualityRenderBuffer = nullptr;
	shared_ptr<RenderBuffer> _highQualityRenderBuffer = nullptr;
	WaterQuality _quality = WaterQuality::SKY;
	TextureID _dudvMap = 0;
	TextureID _normalMap = 0;
	TextureID _displacementMap = 0;
};