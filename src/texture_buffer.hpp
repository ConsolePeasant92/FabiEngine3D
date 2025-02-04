#pragma once

#define GLEW_STATIC

#include "image.hpp"

#include <array>
#include <memory>
#include <glew.h>

using std::shared_ptr;
using std::array;

class TextureBuffer final
{
public:
	TextureBuffer(unsigned int tboId);
	TextureBuffer(shared_ptr<Image> image);
	TextureBuffer(const array<shared_ptr<Image>, 6> & images);
	~TextureBuffer();

	void loadMipMapping();
	void loadAnisotropicFiltering(int quality);

	const unsigned int getTboId() const;

	const bool isMipMapped() const;
	const bool isAnisotropicallyFiltered() const;

private:
	unsigned int _tboId;

	bool _isMipMapped = false;
	bool _isAnisotropicallyFiltered = false;
};