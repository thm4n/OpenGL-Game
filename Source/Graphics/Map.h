#ifndef _MAP_H_
#define _MAP_H_

#include "../main.h"
#include "Chunk.h"

namespace game {
	class Map {
	public:
		Map();
		~Map();

		void update();
		void render(glm::mat4 view, glm::mat4 projection);

		void loadResources();
		void loadShaders();

		void loadMap();

		//generate map
		void generate(int seed);

//		void loadMapFromSave();
//		void saveMap();

	private:
		Chunk* _chunks[MAP_SIZE][MAP_SIZE];

		Shader* _shader;
	};
}

#endif