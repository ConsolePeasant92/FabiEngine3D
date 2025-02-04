#pragma once

#include "vertex_buffer.hpp"
#include "texture_buffer.hpp"

#include <memory>
#include <string>

using std::string;
using std::shared_ptr;

class Quad2d final
{
public:
	Quad2d(const string & id);

	void updateTarget();
	void updateTransformation();
	void setVertexBuffer(shared_ptr<VertexBuffer> value);
	void setDiffuseMap(shared_ptr<TextureBuffer> value);
	void setDiffuseMapPath(const string & value);
	void setHorizontallyFlipped(bool value);
	void setVerticallyFlipped(bool value);
	void setOpacity(float value);
	void setWireframeColor(const fvec3 & value);
	void setColor(const fvec3 & value);
	void setMinClipPosition(const fvec2 & value);
	void setMaxClipPosition(const fvec2 & value);
	void setPosition(const fvec2 & value);
	void setRotation(float value);
	void setSize(const fvec2 & value);
	void move(const fvec2 & change);
	void rotate(float change);
	void scale(const fvec2 & change);
	void moveTo(const fvec2 & target, float speed);
	void rotateTo(float target, float speed);
	void scaleTo(const fvec2 & target, float speed);
	void setDepth(int value);
	void setUvMultiplier(const fvec2 & value);
	void setUvOffset(const fvec2 & value);
	void setWireframed(bool value);
	void setCentered(bool value);
	void setTextureRepeat(int value);
	void setVisible(bool value);
	void setLightness(float value);

	const shared_ptr<VertexBuffer> getVertexBuffer() const;
	const shared_ptr<TextureBuffer> getDiffuseTextureBuffer() const;

	const string & getId() const;
	const string & getDiffuseMapPath() const;

	const fmat44 & getTransformation() const;

	const fvec3 & getWireframeColor() const;
	const fvec3 & getColor() const;

	const fvec2 & getPosition() const;
	const fvec2 & getSize() const;
	const fvec2 & getMinClipPosition() const;
	const fvec2 & getMaxClipPosition() const;
	const fvec2 & getUvMultiplier() const;
	const fvec2 & getUvOffset() const;

	const float getOpacity() const;
	const float getRotation() const;
	const float getLightness() const;

	const int getTextureRepeat() const;
	const int getDepth() const;

	const bool isVisible() const;
	const bool isWireframed() const;
	const bool isCentered() const;
	const bool isHorizontallyFlipped() const;
	const bool isVerticallyFlipped() const;

private:
	const string _id;

	shared_ptr<VertexBuffer> _vertexBuffer = nullptr;
	shared_ptr<TextureBuffer> _diffuseTextureBuffer = nullptr;

	string _diffuseMapPath = "";

	fmat44 _transformation = fmat44(1.0f);

	fvec3 _color = fvec3(1.0f);
	fvec3 _wireframeColor = fvec3(1.0f);

	fvec2 _minClipPosition = fvec2(-1.0f);
	fvec2 _maxClipPosition = fvec2(1.0f);
	fvec2 _position = fvec2(0.0f);
	fvec2 _size = fvec2(1.0f);
	fvec2 _positionTarget = fvec2(0.0f);
	fvec2 _sizeTarget = fvec2(1.0f);
	fvec2 _uvMultiplier = fvec2(1.0f);
	fvec2 _uvOffset = fvec2(0.0f);

	float _rotation = 0.0f;
	float _rotationTarget = 0.0f;
	float _positionTargetSpeed = 0.0f;
	float _rotationTargetSpeed = 0.0f;
	float _sizeTargetSpeed = 0.0f;
	float _opacity = 1.0f;
	float _lightness = 1.0f;

	int _textureRepeat = 1;
	int _depth = 0;

	bool _isCentered = false;
	bool _isHorizontallyFlipped = false;
	bool _isVerticallyFlipped = false;
	bool _isWireframed = false;
	bool _isVisible = true;
};