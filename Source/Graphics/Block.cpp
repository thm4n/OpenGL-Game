#include "Block.h"

namespace game {
	Block::Block(int x, int y, int z, block_t type) {
		this->_pos = glm::vec3(x, y, z);
		this->_type = type;

		float vertices[] = {
			//x   y     z     s     t
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
			1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 
			0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
 
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 
			1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 
			1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 
			1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 
			0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 
 
			0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 
			0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 
			0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 
 
			1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 
			1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 
			1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 
			1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 
			1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 
 
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 
			1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 
			1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 
			1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 
			0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 

			0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 
			1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 
			1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 
			0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 
			0.0f, 1.0f, 0.0f, 0.0f, 1.0f
		};

		glGenVertexArrays(1, &this->_vao);
		glGenBuffers(1, &this->_vbo);
		//glGenBuffers(1, &this->_ebo);

		glBindVertexArray(this->_vao);

		glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	
	Block::~Block() {
		delete this->_shader;
		
		glDeleteVertexArrays(1, &this->_vao);
		glDeleteBuffers(1, &this->_vbo);
		//glDeleteBuffers(1, &this->_ebo);
	}


	void Block::loadShader() {
		this->_shader = new Shader("Block.vs", "Block.fs");
	}

	void Block::loadResources() {
		glGenTextures(1, &this->_texture);
		glBindTexture(GL_TEXTURE_2D, this->_texture);

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

	void Block::update() {
		
	}
		
	void Block::render(glm::mat4 view, glm::mat4 projection) {
		this->_shader->use();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, this->_pos);
		this->_shader->setMat4("model", model);
		this->_shader->setMat4("projection", projection);
		this->_shader->setMat4("view", view);
		this->_shader->setInt("tex", 0);
		
		glBindTexture(GL_TEXTURE_2D, this->_texture);
		glBindVertexArray(this->_vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}
