#pragma once

#include "vertex_buffer.hpp"
#include "texture_buffer.hpp"

#include <memory>
#include <string>

using std::string;
using std::shared_ptr;

class Water final
{
public:
	Water(const string & id);

	void updateOffsets();
	void setLowQualityVertexBuffer(shared_ptr<VertexBuffer> value);
	void setHighQualityVertexBuffer(shared_ptr<VertexBuffer> value);
	void setRippleSpeed(const fvec2 & value);
	void setWaveSpeed(const fvec2 & value);
	void setRippleOffset(const fvec2 & value);
	void setWaveOffset(const fvec2 & value);
	void setColor(const fvec3 & value);
	void setDudvMap(shared_ptr<TextureBuffer> value);
	void setNormalMap(shared_ptr<TextureBuffer> value);
	void setHeightMap(shared_ptr<TextureBuffer> value);
	void setDudvMapPath(const string & value);
	void setNormalMapPath(const string & value);
	void setHeightMapPath(const string & value);
	void setTextureRepeat(int value);
	void setWaveHeight(float value);
	void setSpecularShininess(float value);
	void setSpecularIntensity(float value);
	void setHeight(float value);
	void setSize(float value);
	void setMaxDepth(float value);
	void setLightness(float value);
	void setDistortionSize(float value);
	void setDistortionFactor(float value);
	void setCaptureOffset(float value);
	void setEdged(bool value);
	void setSpecular(bool value);
	void setReflective(bool value);
	void setRefractive(bool value);
	void setWireframed(bool value);
	void setWireframeColor(const fvec3 & value);
	void setMinClipPosition(const fvec3 & value);
	void setMaxClipPosition(const fvec3 & value);
	void setCapturingSky(bool value);
	void setCapturingTerrain(bool value);
	void setCapturingModels(bool value);
	void setCapturingQuad3ds(bool value);
	void setCapturingText3ds(bool value);
	void setCapturingAabbs(bool value);

	const shared_ptr<VertexBuffer> getLowQualityVertexBuffer() const;
	const shared_ptr<VertexBuffer> getHighQualityVertexBuffer() const;
	const shared_ptr<TextureBuffer> getDudvTextureBuffer() const;
	const shared_ptr<TextureBuffer> getNormalTextureBuffer() const;
	const shared_ptr<TextureBuffer> getHeightTextureBuffer() const;

	const string & getId() const;
	const string & getDudvMapPath() const;
	const string & getNormalMapPath() const;
	const string & getHeightMapPath() const;

	const fvec3 & getColor() const;
	const fvec3 & getWireframeColor() const;
	const fvec3 & getMinClipPosition() const;
	const fvec3 & getMaxClipPosition() const;

	const fvec2 & getRippleOffset() const;
	const fvec2 & getRippleSpeed() const;
	const fvec2 & getWaveOffset() const;
	const fvec2 & getWaveSpeed() const;

	const float getHeight() const;
	const float getWaveHeight() const;
	const float getMaxDepth() const;
	const float getSpecularShininess() const;
	const float getSpecularIntensity() const;
	const float getSize() const;
	const float getLightness() const;
	const float getDistortionSize() const;
	const float getDistortionFactor() const;
	const float getCaptureOffset() const;

	const int getTextureRepeat() const;

	const bool isSpecular() const;
	const bool isReflective() const;
	const bool isRefractive() const;
	const bool isWireframed() const;
	const bool isEdged() const;
	const bool isCapturingSky() const;
	const bool isCapturingTerrain() const;
	const bool isCapturingModels() const;
	const bool isCapturingQuad3ds() const;
	const bool isCapturingText3ds() const;
	const bool isCapturingAabbs() const;

private:
	const string _id;

	shared_ptr<VertexBuffer> _lowQualityVertexBuffer = nullptr;
	shared_ptr<VertexBuffer> _highQualityVertexBuffer = nullptr;
	shared_ptr<TextureBuffer> _dudvTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _normalTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _heightTextureBuffer = nullptr;

	string _dudvMapPath = "";
	string _normalMapPath = "";
	string _heightMapPath = "";

	fvec3 _color = fvec3(1.0f);
	fvec3 _wireframeColor = fvec3(1.0f);
	fvec3 _minClipPosition = fvec3(-FLT_MAX);
	fvec3 _maxClipPosition = fvec3(FLT_MAX);

	fvec2 _rippleOffset = fvec2(0.0f);
	fvec2 _rippleSpeed = fvec2(0.0f);
	fvec2 _waveSpeed = fvec2(0.0f);
	fvec2 _waveOffset = fvec2(0.0f);

	float _height = 0.0f;
	float _size = 1.0f;
	float _waveHeight = 0.0f;
	float _maxDepth = 0.0f;
	float _specularShininess = 1.0f;
	float _specularIntensity = 1.0f;
	float _lightness = 1.0f;
	float _distortionFactor = 1.0f;
	float _distortionSize = 1.0f;
	float _captureOffset = 1.0f;

	int _textureRepeat = 1;

	bool _isSpecular = false;
	bool _isEdged = 1.0f;
	bool _isReflective = false;
	bool _isRefractive = false;
	bool _isWireframed = false;
	bool _isCapturingSky = false;
	bool _isCapturingTerrain = false;
	bool _isCapturingModels = false;
	bool _isCapturingQuad3ds = false;
	bool _isCapturingText3ds = false;
	bool _isCapturingAabbs = false;
};