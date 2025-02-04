#pragma warning(disable:6386)

#include "image.hpp"

#include <stdlib.h>

Image::Image(unsigned char * pixels, int width, int height, int bitsPerPixel)
	:
	_pixels(pixels),
	_width(width),
	_height(height),
	_bitsPerPixel(bitsPerPixel)
{
	if(_pixels == nullptr)
	{
		abort();
	}

	if((_width == 0) || (_height == 0))
	{
		abort();
	}
}

Image::~Image()
{
	delete[] _pixels;
}

void Image::flipX()
{
	const auto byteFormat = (_bitsPerPixel / 8);
	const auto size = (_width * _height * byteFormat);
	const auto newPixels = new unsigned char[size];

	for(int y = 0; y < _height; y++)
	{
		for(int x = 0; x < _width; x++)
		{
			const auto index1 = ((x * byteFormat) + (y * _width * byteFormat));
			const auto index2 = (((_width - x - 1) * byteFormat) + (y * _width * byteFormat));

			switch(_bitsPerPixel)
			{
				case 24:
				{
					newPixels[index1 + 0] = _pixels[index2 + 0];
					newPixels[index1 + 1] = _pixels[index2 + 1];
					newPixels[index1 + 2] = _pixels[index2 + 2];

					break;
				}
				case 32:
				{
					newPixels[index1 + 0] = _pixels[index2 + 0];
					newPixels[index1 + 1] = _pixels[index2 + 1];
					newPixels[index1 + 2] = _pixels[index2 + 2];
					newPixels[index1 + 3] = _pixels[index2 + 3];

					break;
				}
			}
		}
	}

	delete[] _pixels;

	_pixels = newPixels;
}

void Image::flipY()
{
	const auto byteFormat = (_bitsPerPixel / 8);
	const auto size = (_width * _height * byteFormat);
	const auto newPixels = new unsigned char[size];

	for(int y = 0; y < _height; y++)
	{
		for(int x = 0; x < _width; x++)
		{
			const auto index1 = ((x * byteFormat) + (y * _width * byteFormat));
			const auto index2 = ((x * byteFormat) + ((_height - y - 1) * _width * byteFormat));

			switch(_bitsPerPixel)
			{
				case 24:
				{
					newPixels[index1 + 0] = _pixels[index2 + 0];
					newPixels[index1 + 1] = _pixels[index2 + 1];
					newPixels[index1 + 2] = _pixels[index2 + 2];

					break;
				}
				case 32:
				{
					newPixels[index1 + 0] = _pixels[index2 + 0];
					newPixels[index1 + 1] = _pixels[index2 + 1];
					newPixels[index1 + 2] = _pixels[index2 + 2];
					newPixels[index1 + 3] = _pixels[index2 + 3];

					break;
				}
			}
		}
	}

	delete[] _pixels;

	_pixels = newPixels;
}

const unsigned char * Image::getPixels() const
{
	return _pixels;
}

const int Image::getWidth() const
{
	return _width;
}

const int Image::getHeight() const
{
	return _height;
}

const int Image::getBitsPerPixel() const
{
	return _bitsPerPixel;
}