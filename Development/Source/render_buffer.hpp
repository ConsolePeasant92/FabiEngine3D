#pragma once

#include "buffer_type.hpp"
#include "mathematics.hpp"
#include "render_utils.hpp"

#include <vector>

using std::vector;

class RenderBuffer final
{
public:
	RenderBuffer() = delete;
	RenderBuffer(RenderBufferType type, const float data[], unsigned int dataCount);   // 3D
	RenderBuffer(float x, float y, float w, float h, bool isCentered); // 2D
	~RenderBuffer();
	
	void enableInstancing(const vector<Vec3>& offsets);
	void disableInstancing();

	const BufferID getVAO();

	const unsigned int getVertexCount();
	
	const bool isInstanced();

	const RenderBufferType getBufferType();

	const vector<Vec3>& getInstancedOffsets();

private:
	// Vectors
	vector<Vec3> _instancedOffsets;

	// Integers
	unsigned int _vertexCount = 0;
	unsigned int _offsetCount = 0;

	// Booleans
	bool _isInstanced = false;

	// Miscellaneosu
	RenderBufferType _bufferType;
	BufferID _vao = 0;
	BufferID _vbo = 0;
	BufferID _vbo_instanced = 0;
};

