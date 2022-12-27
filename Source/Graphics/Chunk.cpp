#include "Chunk.h"

namespace game {
	Chunk::Chunk(int x, int y) {
		this->_pos = glm::vec2(x, y);
		
		for(int i = 0; i < CHUNK_SIZE; i++) {
			//for(int j = 0; j < Y_MAX; j++){
				for(int k = 0; k < CHUNK_SIZE; k++) {
					this->_blocks[i][0][k] = new Block(i, 0, k, block_t::_dirt);
				}
			//}
		}
	}

	Chunk::~Chunk() {
		delete this->_shader;
		for(int i = 0; i < CHUNK_SIZE; i++) {
			//for(int j = 0; j < Y_MAX; j++){
				for(int k = 0; k < CHUNK_SIZE; k++) {
					delete this->_blocks[i][0][k];
				}
			//}
		}
	}

	void Chunk::loadShaders() {
		this->_shader = new Shader("Chunk.vs", "Chunk.fs");
	}

	void Chunk::loadResources() {
		glGenTextures(1, &this->_textures[0]);
		glBindTexture(GL_TEXTURE_2D, this->_textures[0]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;

		unsigned char* data= stbi_load(textures::getTexturePath("Grass.png"), &width, &height, &nrChannels, 0);
		if(!data) {
			throw Exception(Exception::texture_load_error, "Unable to load texture: Resources/Textures/Grass.jpg");
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
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

	void Chunk::render(glm::mat4 view, glm::mat4 projection) {
		this->_shader->use();

		this->_shader->setMat4("projection", projection);
		this->_shader->setMat4("view", view);

		glBindTexture(GL_TEXTURE_2D, this->_textures[0]);
		this->_shader->setInt("tex", 0);

		glm::mat4 model = glm::mat4(1.0f);
		Block* block = nullptr;

		for(int i = 0; i < CHUNK_SIZE; i++) {
			//for(int j = 0; j < Y_MAX; j++){
				for(int k = 0; k < CHUNK_SIZE; k++) {
					block = this->_blocks[i][0][k];
					this->_shader->setMat4("model", glm::translate(model, block->getPos()));
					block->render(view, projection);
				}
			//}
		}
	}
}