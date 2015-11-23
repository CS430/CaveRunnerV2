#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"


GLTexture ImageLoader::loadPNG(const std::string& filePath)
{
	//createing gltextrue on the stack and return a copy
	GLTexture texture = {};		//init all values 

	std::vector<unsigned char> in;
	std::vector<unsigned char> out;

	unsigned long width;
	unsigned long height;

	if (!IOManager::readFileToBUffer(filePath, in))
	{
		fprintf(stderr, "Failed to load PNG file to buffer");
	}
	

	int errorCode = decodePNG(out, width, height, &(in[0]), in.size());

	if (errorCode != 0)
	{
		fprintf(stderr, "decodePNG failed with error: %d", errorCode);
	}

	glGenTextures(1, &(texture.id));

	glBindTexture(GL_TEXTURE_2D, texture.id);
	glEnable(GL_BLEND);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));


	//this deals with what zhang was talking about in class i.e if you image is much larger than your object
	//or if your object is larger than your image
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = width;
	texture.height = height;

	return texture;
}

