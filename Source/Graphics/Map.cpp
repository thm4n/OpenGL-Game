#include "Map.h"

namespace game {
	Map::Map() {
		
	}

	Map::~Map() {
		for(size_t i = 0; i < MAP_SIZE; i++)
			for(size_t j = 0; j < MAP_SIZE; j++)
				delete this->_chunks[i][j];
	}

	void Map::loadShaders() {
		this->_shader = new Shader("Chunk.vs", "Chunk.fs");
		Chunk::setShader(this->_shader);
	}

	void Map::loadResources() {
		Block::loadTextures();
	}

	void Map::loadMap() {
		glm::ivec2 coords(-MAP_SIZE, -MAP_SIZE);
		coords /= 2;
		for(size_t i = 0; i < MAP_SIZE; i++) 
			for(size_t j = 0; j < MAP_SIZE; j++)
				this->_chunks[i][j] = new Chunk(i + coords.x, j + coords.y);
	}

	void Map::update() {
		for(size_t i = 0; i < MAP_SIZE; i++)
			for(size_t j = 0; j < MAP_SIZE; j++)
				this->_chunks[i][j]->update();
	}

	void Map::render(glm::mat4 view, glm::mat4 projection) {
		this->_shader->use();

		this->_shader->setMat4("projection", projection);
		this->_shader->setMat4("view", view);

		for(size_t i = 0; i < MAP_SIZE; i++)
			for(size_t j = 0; j < MAP_SIZE; j++)
				this->_chunks[i][j]->render();
	}
}
