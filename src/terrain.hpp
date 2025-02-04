#pragma once

#include "vertex_buffer.hpp"
#include "texture_buffer.hpp"

#include <memory>
#include <string>

using std::string;
using std::shared_ptr;

class Terrain final
{
public:
	Terrain(const string & id);

	void setVertexBuffer(shared_ptr<VertexBuffer> value);
	void setPixels(const vector<float> & value);
	void setHeightMapPath(const string & value);
	void setDiffuseMap(shared_ptr<TextureBuffer> value);
	void setDiffuseMapPath(const string & value);
	void setNormalMap(shared_ptr<TextureBuffer> value);
	void setNormalMapPath(const string & value);
	void setBlendMap(shared_ptr<TextureBuffer> value);
	void setBlendMapPath(const string & value);
	void setRedDiffuseMap(shared_ptr<TextureBuffer> value);
	void setRedDiffuseMapPath(const string & value);
	void setGreenDiffuseMap(shared_ptr<TextureBuffer> value);
	void setGreenDiffuseMapPath(const string & value);
	void setBlueDiffuseMap(shared_ptr<TextureBuffer> value);
	void setBlueDiffuseMapPath(const string & value);
	void setRedNormalMap(shared_ptr<TextureBuffer> value);
	void setRedNormalMapPath(const string & value);
	void setGreenNormalMap(shared_ptr<TextureBuffer> value);
	void setGreenNormalMapPath(const string & value);
	void setBlueNormalMap(shared_ptr<TextureBuffer> value);
	void setBlueNormalMapPath(const string & value);
	void setTextureRepeat(int value);
	void setRedTextureRepeat(int value);
	void setGreenTextureRepeat(int value);
	void setBlueTextureRepeat(int value);
	void setSize(float value);
	void setMaxHeight(float value);
	void setLightness(float value);
	void setSpecularShininess(float value);
	void setSpecularIntensity(float value);
	void setSpecular(bool value);
	void setWireframed(bool value);
	void setShadowed(bool value);
	void setWireframeColor(const fvec3 & value);
	void setColor(const fvec3 & value);
	void setMinClipPosition(const fvec3 & value);
	void setMaxClipPosition(const fvec3 & value);

	const vector<float> & getPixels() const;

	const shared_ptr<VertexBuffer> getVertexBuffer() const;
	const shared_ptr<TextureBuffer> getDiffuseTextureBuffer() const;
	const shared_ptr<TextureBuffer> getNormalTextureBuffer() const;
	const shared_ptr<TextureBuffer> getBlendTextureBuffer() const;
	const shared_ptr<TextureBuffer> getRedDiffuseTextureBuffer() const;
	const shared_ptr<TextureBuffer> getGreenDiffuseTextureBuffer() const;
	const shared_ptr<TextureBuffer> getBlueDiffuseTextureBuffer() const;
	const shared_ptr<TextureBuffer> getRedNormalTextureBuffer() const;
	const shared_ptr<TextureBuffer> getGreenNormalTextureBuffer() const;
	const shared_ptr<TextureBuffer> getBlueNormalTextureBuffer() const;

	const string & getId() const;
	const string & getHeightMapPath() const;
	const string & getDiffuseMapPath() const;
	const string & getNormalMapPath() const;
	const string & getBlendMapPath() const;
	const string & getRedDiffuseMapPath() const;
	const string & getGreenDiffuseMapPath() const;
	const string & getBlueDiffuseMapPath() const;
	const string & getRedNormalMapPath() const;
	const string & getGreenNormalMapPath() const;
	const string & getBlueNormalMapPath() const;

	const fvec3 & getColor() const;
	const fvec3 & getWireframeColor() const;
	const fvec3 & getMinClipPosition() const;
	const fvec3 & getMaxClipPosition() const;

	const float getSize() const;
	const float getMaxHeight() const;
	const float getLightness() const;
	const float getSpecularShininess() const;
	const float getSpecularIntensity() const;

	const int getRedTextureRepeat() const;
	const int getGreenTextureRepeat() const;
	const int getBlueTextureRepeat() const;
	const int getTextureRepeat() const;

	const bool isSpecular() const;
	const bool isWireframed() const;
	const bool isShadowed() const;

private:
	const string _id;

	vector<float> _pixels = {};

	shared_ptr<VertexBuffer> _vertexBuffer = nullptr;
	shared_ptr<TextureBuffer> _diffuseTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _normalTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _blendTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _redDiffuseTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _greenDiffuseTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _blueDiffuseTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _redNormalTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _greenNormalTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _blueNormalTextureBuffer = nullptr;

	string _heightMapPath = "";
	string _diffuseMapPath = "";
	string _normalMapPath = "";
	string _blendMapPath = "";
	string _redDiffuseMapPath = "";
	string _greenDiffuseMapPath = "";
	string _blueDiffuseMapPath = "";
	string _redNormalMapPath = "";
	string _greenNormalMapPath = "";
	string _blueNormalMapPath = "";

	fvec3 _color = fvec3(1.0f);
	fvec3 _wireframeColor = fvec3(1.0f);
	fvec3 _minClipPosition = fvec3(-FLT_MAX);
	fvec3 _maxClipPosition = fvec3(FLT_MAX);

	float _maxHeight = 1.0f;
	float _size = 0.0f;
	float _lightness = 1.0f;
	float _specularShininess = 1.0f;
	float _specularIntensity = 1.0f;

	int _redTextureRepeat = 1;
	int _greenTextureRepeat = 1;
	int _blueTextureRepeat = 1;
	int _textureRepeat = 1;

	bool _isSpecular = false;
	bool _isWireframed = false;
	bool _isShadowed = false;
};