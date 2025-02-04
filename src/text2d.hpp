#pragma once

#include "quad2d.hpp"

#include <memory>
#include <unordered_map>

using std::shared_ptr;
using std::unordered_map;

class Text2d final
{
public:
	Text2d(const string & id);

	void updateTarget();
	void updateQuad2ds();
	void setVertexBuffer(shared_ptr<VertexBuffer> value);
	void setContent(const string & value);
	void setFontMapPath(const string & value);
	void setFontMap(shared_ptr<TextureBuffer> value);
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
	void setWireframed(bool value);
	void setCentered(bool value);
	void setVisible(bool value);
	void setLightness(float value);

	const vector<shared_ptr<Quad2d>> & getQuad2ds() const;

	const shared_ptr<VertexBuffer> getVertexBuffer() const;
	const shared_ptr<TextureBuffer> getFontTextureBuffer() const;

	const string & getId() const;
	const string & getContent() const;
	const string & getFontMapPath() const;

	const fvec3 & getWireframeColor() const;
	const fvec3 & getColor() const;

	const fvec2 & getPosition() const;
	const fvec2 & getSize() const;
	const fvec2 & getMinClipPosition() const;
	const fvec2 & getMaxClipPosition() const;

	const float getOpacity() const;
	const float getRotation() const;
	const float getLightness() const;

	const int getDepth() const;

	const bool isVisible() const;
	const bool isWireframed() const;
	const bool isCentered() const;
	const bool isHorizontallyFlipped() const;
	const bool isVerticallyFlipped() const;

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

	vector<shared_ptr<Quad2d>> _quad2ds = {};

	shared_ptr<VertexBuffer> _vertexBuffer = nullptr;
	shared_ptr<TextureBuffer> _fontTextureBuffer = nullptr;

	string _content = "";
	string _fontMapPath = "";

	fvec3 _color = fvec3(1.0f);
	fvec3 _wireframeColor = fvec3(1.0f);

	fvec2 _minClipPosition = fvec2(-1.0f);
	fvec2 _maxClipPosition = fvec2(1.0f);
	fvec2 _position = fvec2(0.0f);
	fvec2 _size = fvec2(1.0f);
	fvec2 _positionTarget = fvec2(0.0f);
	fvec2 _sizeTarget = fvec2(1.0f);

	float _rotation = 0.0f;
	float _rotationTarget = 0.0f;
	float _positionTargetSpeed = 0.0f;
	float _rotationTargetSpeed = 0.0f;
	float _sizeTargetSpeed = 0.0f;
	float _opacity = 1.0f;
	float _lightness = 1.0f;

	int _depth = 0;

	bool _isCentered = false;
	bool _isHorizontallyFlipped = false;
	bool _isVerticallyFlipped = false;
	bool _isWireframed = false;
	bool _isVisible = true;
};