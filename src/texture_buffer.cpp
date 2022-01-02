#include "texture_buffer.hpp"

TextureBuffer::TextureBuffer(shared_ptr<Image> image, bool isMipmapped, bool isAnisotropic)
{
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	if(image->getPixelFormat() == PixelFormat::GRAY)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, image->getWidth(), image->getHeight(), 0, GL_RED, GL_UNSIGNED_BYTE, image->getPixels());
	}
	if(image->getPixelFormat() == PixelFormat::RGB)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getPixels());
	}
	if(image->getPixelFormat() == PixelFormat::RGBA)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixels());
	}

	if(isMipmapped)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	if(isAnisotropic)
	{
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, static_cast<int>(_anisotropicFilteringQuality));
	}
}

TextureBuffer::TextureBuffer(const array<shared_ptr<Image>, 6>& images)
{
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);

	for(size_t i = 0; i < images.size(); i++)
	{
		const auto image = images[i];
		const auto index = (GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<unsigned int>(i));

		if(image == nullptr)
		{
			glTexImage2D(index, 0, GL_RGB, images[i]->getWidth(), images[i]->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
			continue;
		}

		if(image->getPixelFormat() == PixelFormat::GRAY)
		{
			glTexImage2D(index, 0, GL_RED, image->getWidth(), image->getHeight(), 0, GL_RED, GL_UNSIGNED_BYTE, image->getPixels());
		}
		if(image->getPixelFormat() == PixelFormat::RGB)
		{
			glTexImage2D(index, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getPixels());
		}
		if(image->getPixelFormat() == PixelFormat::RGBA)
		{
			glTexImage2D(index, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixels());
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

TextureBuffer::~TextureBuffer()
{
	glDeleteTextures(1, &_texture);
}

const BufferID TextureBuffer::getTexture()
{
	return _texture;
}

//void ImageLoader::_reloadAnisotropicFiltering()
//{
//	for(const auto& [path, texture] : _2dTextureCache)
//	{
//		glBindTexture(GL_TEXTURE_2D, texture);
//
//		int currentQuality;
//		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &currentQuality);
//
//		if((currentQuality >= Config::MIN_ANISOTROPIC_FILTERING_QUALITY) && (currentQuality <= Config::MAX_ANISOTROPIC_FILTERING_QUALITY))
//		{
//			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, static_cast<int>(_anisotropicFilteringQuality));
//		}
//
//		glBindTexture(GL_TEXTURE_2D, 0);
//	}
//}
//
//void ImageLoader::setAnisotropicFilteringQuality(unsigned int value)
//{
//	_anisotropicFilteringQuality = clamp(value, Config::MIN_ANISOTROPIC_FILTERING_QUALITY, Config::MAX_ANISOTROPIC_FILTERING_QUALITY);
//	_reloadAnisotropicFiltering();
//}
//
//const unsigned int ImageLoader::getAnisotropicFilteringQuality()const
//{
//	return _anisotropicFilteringQuality;
//}