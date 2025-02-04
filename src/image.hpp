#pragma once

class Image final
{
public:
	Image(unsigned char * pixels, int width, int height, int bitsPerPixel);
	~Image();

	void flipX();
	void flipY();

	const unsigned char * getPixels() const;

	const int getWidth() const;
	const int getHeight() const;
	const int getBitsPerPixel() const;

private:
	const unsigned char * _pixels;

	const int _width;
	const int _height;

	const int _bitsPerPixel;
};