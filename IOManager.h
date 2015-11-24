#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <vector>

class IOManager {
public:
	static bool readFileToBUffer(std::string filePath, std::vector<unsigned char>& buffer);
};

#endif