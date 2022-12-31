#include "Map.h"

namespace game {
	namespace Map {
		Chunk* _chunks[MAP_SIZE][MAP_SIZE];

		Shader* _shader;

		void freeChunks() {
			for(size_t i = 0; i < MAP_SIZE; i++)
				for(size_t j = 0; j < MAP_SIZE; j++)
					delete Map::_chunks[i][j];
		}

		void loadShaders() {
			Map::_shader = new Shader("Chunk.vs", "Chunk.fs");
			Chunk::setShader(Map::_shader);
		}

		void loadResources() {
			Block::loadTextures();
		}

		void loadMap() {
			glm::ivec2 coords(-MAP_SIZE, -MAP_SIZE);
			coords /= 2;
			for(size_t i = 0; i < MAP_SIZE; i++) 
				for(size_t j = 0; j < MAP_SIZE; j++)
					Map::_chunks[i][j] = new Chunk(i + coords.x, j + coords.y);
		}

		void update() {
			for(size_t i = 0; i < MAP_SIZE; i++)
				for(size_t j = 0; j < MAP_SIZE; j++)
					Map::_chunks[i][j]->update();
		}

		void render(glm::mat4 view, glm::mat4 projection) {
			Map::_shader->use();

			Map::_shader->setMat4("projection", projection);
			Map::_shader->setMat4("view", view);

			for(size_t i = 0; i < MAP_SIZE; i++)
				for(size_t j = 0; j < MAP_SIZE; j++)
					Map::_chunks[i][j]->render();
		}

		Block* getFirstBlockBelowPos(glm::vec3 position) {
			int x = position.x;
			x = (x - (x % CHUNK_SIZE)) * (x > 0 ? 1 : -1);

			int z = position.z;
			z = (z - (z % CHUNK_SIZE)) * (z > 0 ? 1 : -1);

			glm::ivec3 temp = position - glm::vec3(x, position.y, z);

			x /= CHUNK_SIZE;
			z /= CHUNK_SIZE;

			x += CHUNK_SIZE / 2;
			z += CHUNK_SIZE / 2;

			printf("\nChunk Coords: (%d, %d)\n", x, z);
			printf("Chunk Location: (%d, %d)\n", x, z);
			return Map::_chunks[x][z]->getFirstBlockBelowPos(temp);
		}
	}
}
