#pragma once

#include "quad3d.hpp"

#include <unordered_map>
#include <memory>

using std::unordered_map;
using std::shared_ptr;

class Text3d final
{
public:
	Text3d(const string & id);

	void updateTarget();
	void updateQuad3ds();
	void setVertexBuffer(shared_ptr<VertexBuffer> value);
	void setContent(const string & value);
	void setFontMapPath(const string & value);
	void setFontMap(shared_ptr<TextureBuffer> value);
	void setFacingCameraHorizontally(bool value);
	void setFacingCameraVertically(bool value);
	void setShadowed(bool value);
	void setCentered(bool value);
	void setReflected(bool value);
	void setRefracted(bool value);
	void setBright(bool value);
	void setWireframed(bool value);
	void setPosition(const fvec3 & value);
	void setRotation(const fvec3 & value);
	void setSize(const fvec2 & value);
	void move(const fvec3 & change);
	void rotate(const fvec3 & change);
	void scale(const fvec2 & change);
	void moveTo(const fvec3 & target, float speed);
	void rotateTo(const fvec3 & target, float speed);
	void scaleTo(const fvec2 & target, float speed);
	void setColor(const fvec3 & value);
	void setWireframeColor(const fvec3 & value);
	void setLightness(float value);
	void setOpacity(float value);
	void setMinClipPosition(const fvec3 & value);
	void setMaxClipPosition(const fvec3 & value);
	void setMinAlpha(float value);
	void setHorizontallyFlipped(bool value);
	void setVerticallyFlipped(bool value);
	void setRotationOrder(DirectionOrderType value);
	void setVisible(bool value);

	const vector<shared_ptr<Quad3d>> & getQuad3ds() const;

	const shared_ptr<VertexBuffer> getVertexBuffer() const;
	const shared_ptr<TextureBuffer> getFontTextureBuffer() const;

	const string & getId() const;
	const string & getContent() const;
	const string & getFontMapPath() const;

	const fmat44 & getTransformation() const;

	const fvec3 & getPosition() const;
	const fvec3 & getRotation() const;
	const fvec3 & getColor() const;
	const fvec3 & getWireframeColor() const;
	const fvec3 & getMinClipPosition() const;
	const fvec3 & getMaxClipPosition() const;

	const fvec2 & getSize() const;
	const fvec2 & getUvMultiplier() const;
	const fvec2 & getUvOffset() const;

	const float getMinAlpha() const;
	const float getLightness() const;
	const float getOpacity() const;

	const bool isVisible() const;
	const bool isFacingCameraHorizontally() const;
	const bool isFacingCameraVertically() const;
	const bool isShadowed() const;
	const bool isReflected() const;
	const bool isRefracted() const;
	const bool isBright() const;
	const bool isWireframed() const;
	const bool isCentered() const;
	const bool isHorizontallyFlipped() const;
	const bool isVerticallyFlipped() const;

	const DirectionOrderType getRotationOrder() const;

private:
	static inline const unordered_map<char, ivec2> _fontMapIndices =
	{
		{' ', ivec2(0, 5)},
		{'!', ivec2(1, 5)},
		{'"', ivec2(2, 5)},
		{'#', ivec2(3, 5)},
		{'$', ivec2(4, 5)},
		{'%', ivec2(5, 5)},
		{'&', ivec2(6, 5)},
		{'\'', ivec2(7, 5)},
		{'(', ivec2(8, 5)},
		{')', ivec2(9, 5)},
		{'*', ivec2(10, 5)},
		{'+', ivec2(11, 5)},
		{',', ivec2(12, 5)},
		{'-', ivec2(13, 5)},
		{'.', ivec2(14, 5)},
		{'/', ivec2(15, 5)},
		{'0', ivec2(0, 4)},
		{'1', ivec2(1, 4)},
		{'2', ivec2(2, 4)},
		{'3', ivec2(3, 4)},
		{'4', ivec2(4, 4)},
		{'5', ivec2(5, 4)},
		{'6', ivec2(6, 4)},
		{'7', ivec2(7, 4)},
		{'8', ivec2(8, 4)},
		{'9', ivec2(9, 4)},
		{':', ivec2(10, 4)},
		{';', ivec2(11, 4)},
		{'<', ivec2(12, 4)},
		{'=', ivec2(13, 4)},
		{'>', ivec2(14, 4)},
		{'?', ivec2(15, 4)},
		{'@', ivec2(0, 3)},
		{'A', ivec2(1, 3)},
		{'B', ivec2(2, 3)},
		{'C', ivec2(3, 3)},
		{'D', ivec2(4, 3)},
		{'E', ivec2(5, 3)},
		{'F', ivec2(6, 3)},
		{'G', ivec2(7, 3)},
		{'H', ivec2(8, 3)},
		{'I', ivec2(9, 3)},
		{'J', ivec2(10, 3)},
		{'K', ivec2(11, 3)},
		{'L', ivec2(12, 3)},
		{'M', ivec2(13, 3)},
		{'N', ivec2(14, 3)},
		{'O', ivec2(15, 3)},
		{'P', ivec2(0, 2)},
		{'Q', ivec2(1, 2)},
		{'R', ivec2(2, 2)},
		{'S', ivec2(3, 2)},
		{'T', ivec2(4, 2)},
		{'U', ivec2(5, 2)},
		{'V', ivec2(6, 2)},
		{'W', ivec2(7, 2)},
		{'X', ivec2(8, 2)},
		{'Y', ivec2(9, 2)},
		{'Z', ivec2(10, 2)},
		{'[', ivec2(11, 2)},
		{'\\', ivec2(12, 2)},
		{']', ivec2(13, 2)},
		{'^', ivec2(14, 2)},
		{'_', ivec2(15, 2)},
		{'`', ivec2(0, 1)},
		{'a', ivec2(1, 1)},
		{'b', ivec2(2, 1)},
		{'c', ivec2(3, 1)},
		{'d', ivec2(4, 1)},
		{'e', ivec2(5, 1)},
		{'f', ivec2(6, 1)},
		{'g', ivec2(7, 1)},
		{'h', ivec2(8, 1)},
		{'i', ivec2(9, 1)},
		{'j', ivec2(10, 1)},
		{'k', ivec2(11, 1)},
		{'l', ivec2(12, 1)},
		{'m', ivec2(13, 1)},
		{'n', ivec2(14, 1)},
		{'o', ivec2(15, 1)},
		{'p', ivec2(0, 0)},
		{'q', ivec2(1, 0)},
		{'r', ivec2(2, 0)},
		{'s', ivec2(3, 0)},
		{'t', ivec2(4, 0)},
		{'u', ivec2(5, 0)},
		{'v', ivec2(6, 0)},
		{'w', ivec2(7, 0)},
		{'x', ivec2(8, 0)},
		{'y', ivec2(9, 0)},
		{'z', ivec2(10, 0)},
		{'{', ivec2(11, 0)},
		{'|', ivec2(12, 0)},
		{'}', ivec2(13, 0)},
		{'~', ivec2(14, 0)}
	};

	static inline constexpr int FONT_MAP_ROW_COUNT = 6;
	static inline constexpr int FONT_MAP_COLUMN_COUNT = 16;

	const string _id;

	vector<shared_ptr<Quad3d>> _quad3ds = {};

	shared_ptr<VertexBuffer> _vertexBuffer = nullptr;
	shared_ptr<TextureBuffer> _fontTextureBuffer = nullptr;

	string _content = "";
	string _fontMapPath = "";

	fmat44 _transformation = fmat44(1.0f);

	fvec3 _position = fvec3(0.0f);
	fvec3 _rotation = fvec3(0.0f);
	fvec3 _positionTarget = fvec3(0.0f);
	fvec3 _rotationTarget = fvec3(0.0f);
	fvec3 _color = fvec3(1.0f);
	fvec3 _wireframeColor = fvec3(1.0f);
	fvec3 _minClipPosition = fvec3(-FLT_MAX);
	fvec3 _maxClipPosition = fvec3(FLT_MAX);

	fvec2 _size = fvec2(1.0f);
	fvec2 _sizeTarget = fvec2(1.0f);
	fvec2 _uvMultiplier = fvec2(1.0f);
	fvec2 _uvOffset = fvec2(0.0f);

	float _minAlpha = 1.0f;
	float _positionTargetSpeed = 0.0f;
	float _rotationTargetSpeed = 0.0f;
	float _sizeTargetSpeed = 0.0f;
	float _lightness = 1.0f;
	float _opacity = 1.0f;

	bool _isFacingCameraHorizontally = false;
	bool _isFacingCameraVertically = false;
	bool _isShadowed = true;
	bool _isReflected = true;
	bool _isRefracted = true;
	bool _isBright = false;
	bool _isWireframed = false;
	bool _isCentered = false;
	bool _isHorizontallyFlipped = false;
	bool _isVerticallyFlipped = false;
	bool _isVisible = true;

	DirectionOrderType _rotationOrder = DirectionOrderType::YXZ;
};