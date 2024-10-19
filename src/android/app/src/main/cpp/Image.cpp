#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_TGA

#include "stb_image.h"

Image::Image(Image&& image)
{
	this->m_colors = image.m_colors;
	this->m_width = image.m_width;
	this->m_height = image.m_height;
	this->m_channels = image.m_channels;
	image.m_colors = nullptr;
}

Image::Image(const std::vector<uint8>& imageBytes)
{
	stbi_uc* stbImage = stbi_load_from_memory(imageBytes.data(), imageBytes.size(), &m_width, &m_height, &m_channels, STBI_rgb_alpha);
	if (!stbImage)
		return;
	for (size_t i = 0; i < m_width * m_height * 4; i += 4)
	{
		uint8 r = stbImage[i];
		uint8 g = stbImage[i + 1];
		uint8 b = stbImage[i + 2];
		uint8 a = stbImage[i + 3];
		stbImage[i] = b;
		stbImage[i + 1] = g;
		stbImage[i + 2] = r;
		stbImage[i + 3] = a;
	}
	m_colors = reinterpret_cast<sint32*>(stbImage);
}

bool Image::isOk() const
{
	return m_colors != nullptr;
}

Image::~Image()
{
	if (m_colors)
		stbi_image_free(m_colors);
}
