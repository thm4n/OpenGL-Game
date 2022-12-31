#ifndef _MAP_H_
#define _MAP_H_

#include "../main.h"
#include "Chunk.h"

namespace game {
	namespace Map {
		void freeChunks();

		void update();
		void render(glm::mat4 view, glm::mat4 projection);

		void loadResources();
		void loadShaders();

		void loadMap();

		//generate map
		void generate(int seed);

//		void loadMapFromSave();
//		void saveMap();

		Block* getFirstBlockBelowPos(glm::vec3 position);
	};
}

#endif