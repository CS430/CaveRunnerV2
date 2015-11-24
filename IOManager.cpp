#include "IOManager.h"

#include <fstream>

bool IOManager::readFileToBUffer(std::string filePath, std::vector<unsigned char>& buffer) {
	std::ifstream file(filePath, std::ios::binary);

	if (file.fail()) {
		fprintf(stderr, "Error reading file: %s", filePath);
		return false;
	}

	//seek to end 
	file.seekg(0, std::ios::end);
	//get filezi
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char *) &(buffer[0]),fileSize);
	file.close();

	return true;
}