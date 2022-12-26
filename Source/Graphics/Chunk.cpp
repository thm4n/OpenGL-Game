#include "Chunk.h"

namespace game {
	Chunk::Chunk(int x, int y) {
		this->_pos = glm::vec2(x, y);
	}

	Chunk::~Chunk() {

	}

	void Chunk::update() {

	}

	void Chunk::render(glm::mat4 view, glm::mat4 projection) {
UNUSED(view);
UNUSED(projection);
	}
}