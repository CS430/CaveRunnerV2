#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <string>

#include "GLTexture.h"

class ImageLoader {
public:
	static GLTexture loadPNG(const std::string& filePath);
};

#endif