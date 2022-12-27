#include "Block.h"

namespace game {
	Block::Block() {
		
	}

	Block::Block(int x, int y, int z, block_t type) {
		this->setVals(x,y,z,type);

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

		printf("game::Block::Block(int,int,int,block_t) was called!\n");
	}
	
	void Block::setVals(int x, int y, int z, block_t type) {
		this->_pos = glm::vec3(x,y,z);
		this->_type = type;
	}

	Block::~Block() {
		printf("game::Block::~Block() was called!\n");

		glDeleteVertexArrays(1, &this->_vao);
		glDeleteBuffers(1, &this->_vbo);
		//glDeleteBuffers(1, &this->_ebo);
	}

	glm::vec3 Block::getPos() const {
		return this->_pos;
	}

	void Block::update() {
		
	}
		
	void Block::render(glm::mat4 view, glm::mat4 projection) {
UNUSED(view);
UNUSED(projection);

		glBindVertexArray(this->_vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
}
