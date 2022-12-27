#ifndef _PATHS_DEFS_H_
#define _PATHS_DEFS_H_

#include "Includes.h"

namespace textures {
	void loadPathList(std::string dirPath);
	void fixPathsList(std::vector<std::string> paths, std::string dirPath);

	const char* getTexturePath(unsigned int texid);
	const char* getTexturePath(std::string texname);
}

#endif