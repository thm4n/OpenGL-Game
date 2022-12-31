#include "Chunk.h"

namespace game {
	Shader* Chunk::_shader;

	Chunk::Chunk(int x, int y) {
		this->_pos = glm::vec2(x, y);
		
		for(int i = 0; i < CHUNK_SIZE; i++) {
			for(int j = 0; j < Y_MAX; j++){
				for(int k = 0; k < CHUNK_SIZE; k++) {
					this->_blocks[i][j][k] = j == 0 ? new Block(i, 0, k, block_t::_dirt) : nullptr;
				}
			}
		}
	}

	Chunk::~Chunk() {
		for(int i = 0; i < CHUNK_SIZE; i++) {
			//for(int j = 0; j < Y_MAX; j++){
				for(int k = 0; k < CHUNK_SIZE; k++) {
					delete this->_blocks[i][0][k];
				}
			//}
		}
	}

	void Chunk::setShader(Shader* shader) {
		Chunk::_shader = shader;
		Block::setShader(shader);
	}

	void Chunk::update() {
		for(int i = 0; i < CHUNK_SIZE; i++) {
			//for(int j = 0; j < Y_MAX; j++){
				for(int k = 0; k < CHUNK_SIZE; k++) {
					this->_blocks[i][0][k]->update();
				}
			//}
		}
	}

	void Chunk::render() {
		this->_shader->use();

		this->_shader->setVec2("chunk", glm::vec2(0.0f,0.0f));

		glm::mat4 model = glm::mat4(1.0f);
		Block* block = nullptr;

		glm::vec3 temp;

		for(int i = 0; i < CHUNK_SIZE; i++) {
			//for(int j = 0; j < Y_MAX; j++){
				for(int k = 0; k < CHUNK_SIZE; k++) {
					block = this->_blocks[i][0][k];
					temp = glm::vec3(this->_pos * (float)CHUNK_SIZE, 0);
					temp.z = temp.y;
					temp.y = 0;
					this->_shader->setMat4("model", glm::translate(model, block->getPos() + temp));
					block->render();
				}
			//}
		}
	}

	Block* Chunk::getFirstBlockBelowPos(glm::vec3 position) {
		Block* temp = nullptr;
		int x = position.x * (position.x > 0 ? 1 : -1);
		int z = position.z * (position.z > 0 ? 1 : -1);

		for(int i = position.y - 1; i >= 0; i--) {
			temp = this->_blocks[x][i][z];
			if(temp != nullptr)
				return temp;
		}
		std::cout << "\nNULL OUT \n";
		return nullptr;
	}
}