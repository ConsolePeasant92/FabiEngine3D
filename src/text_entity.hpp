#pragma once

#include "image_entity.hpp"
#include "render_buffer.hpp"
#include "texture_loader.hpp"

#include <memory>

using std::shared_ptr;

class TextEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	void updateTransformation();
	void updateCharacterEntities();
	void setRenderBuffer(shared_ptr<RenderBuffer> value);
	void setContent(const string& value, TextureLoader& textureLoader);
	void setFontPath(const string& value);
	void setDiffuseMap(TextureID value);
	void setDiffuseMapPath(const string& value);
	void setMirroredHorizontally(bool value);
	void setMirroredVertically(bool value);
	void setTransparency(float value);
	void setWireframeColor(fvec3 value);
	void setColor(fvec3 value);
	void setMinPosition(fvec2 value);
	void setMaxPosition(fvec2 value);
	void setPosition(fvec2 value);
	void setRotation(float value);
	void setSize(fvec2 value);
	void move(fvec2 value);
	void rotate(float value);
	void scale(fvec2 value);
	void moveTo(fvec2 target, float speed);
	void rotateTo(float target, float speed);
	void scaleTo(fvec2 target, float speed);
	void setDepth(unsigned int value);
	void setWireframed(bool value);
	void setCentered(bool value);

	const string& getContent() const;
	const string& getFontPath() const;
	const string& getDiffuseMapPath() const;

	const fvec3 getWireframeColor() const;
	const fvec3 getColor() const;

	const fvec2 getPosition() const;
	const fvec2 getSize() const;
	const fvec2 getMinPosition() const;
	const fvec2 getMaxPosition() const;

	const float getTransparency() const;
	const float getRotation() const;

	const unsigned int getDepth() const;

	const bool isWireframed() const;
	const bool isCentered() const;
	const bool isMirroredHorizonally() const;
	const bool isMirroredVertically() const;
	const bool hasDiffuseMap() const;

	const TextureID getDiffuseMap() const;

	const vector<shared_ptr<ImageEntity>>& getCharacterEntities() const;

private:
	string _content = "";
	string _fontPath = "";
	string _diffuseMapPath = "";

	fvec3 _color = fvec3(1.0f);
	fvec3 _wireframeColor = fvec3(1.0f);

	fvec2 _minPosition = fvec2(-1.0f);
	fvec2 _maxPosition = fvec2(1.0f);
	fvec2 _position = fvec2(0.0f);
	fvec2 _size = fvec2(1.0f);
	fvec2 _positionTarget = fvec2(0.0f);
	fvec2 _sizeTarget = fvec2(1.0f);

	float _rotation = 0.0f;
	float _rotationTarget = 0.0f;
	float _positionTargetSpeed = 0.0f;
	float _rotationTargetSpeed = 0.0f;
	float _sizeTargetSpeed = 0.0f;
	float _transparency = 1.0f;

	unsigned int _depth = 0;

	bool _isCentered = false;
	bool _isMirroredHorizontally = false;
	bool _isMirroredVertically = false;
	bool _isWireframed = false;

	vector<shared_ptr<ImageEntity>> _characterEntities;
	shared_ptr<RenderBuffer> _renderBuffer = nullptr;
	TextureID _diffuseMap = 0;
};