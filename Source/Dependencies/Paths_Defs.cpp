#include "Paths_Defs.h"

#include <dirent.h>

namespace textures {
	std::map<std::pair<unsigned int, std::string>, std::string> _paths; //<<id, name>, path>

	void loadPathList(std::string dirPath) {
		std::vector<std::string> paths;

		DIR* dir = opendir(dirPath.c_str());
		struct dirent *entry = nullptr;

		if(!dir) {
			throw Exception(Exception::file_dir_open_error, "Unable to open directory: " + dirPath);
		}

		std::string temp;
		while((entry = readdir(dir)) != NULL) {
			temp = entry->d_name;
			if(temp.find_first_of('_') != std::string::npos)
				paths.push_back(temp);
		}
		closedir(dir);
		
		fixPathsList(paths, dirPath);

	}

	void fixPathsList(std::vector<std::string> paths, std::string dirPath) {
		//each file is named: <texID>_<texName>.<file type>
		std::string str;
		size_t dash = std::string::npos;
		std::pair<unsigned int, std::string> identifiers; //id, name;
		for(size_t i = 0; i < paths.size(); i++) {
			str = paths[i];
			dash = str.find_first_of('_');
			identifiers = std::make_pair(std::stoi(str.substr(0, dash)), str.substr(dash+1));
			_paths.insert(std::make_pair(identifiers, dirPath + str));
		}
	}

	const char* getTexturePath(unsigned int texid) {
		for(auto mapit = _paths.begin(); mapit != _paths.end(); mapit++)
			if(mapit->first.first == texid)
				return mapit->second.c_str();
		return "";
	}

	const char* getTexturePath(std::string texname) {
		for(auto mapit = _paths.begin(); mapit != _paths.end(); mapit++)
			if(mapit->first.second == texname)
				return mapit->second.c_str();
		return "";
	}
}
