#pragma once

struct TextureData
{
public:
	TextureData(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int channelCount);

	const unsigned char* getPixels();

	const unsigned int getWidth();
	const unsigned int getHeight();
	const unsigned int getChannelCount();

private:
	const unsigned char* _pixels;

	unsigned int _width;
	unsigned int _height;
	unsigned int _channelCount;
};