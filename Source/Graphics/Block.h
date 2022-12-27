#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "../main.h"

namespace game {
	class Block {
	public:
		Block();
		Block(int x, int y, int z, block_t type);
		~Block();

		void setVals(int x, int y, int z, block_t type);

		glm::vec3 getPos() const;

		void update();
		void render(glm::mat4 view, glm::mat4 projection);

	private:
		unsigned int _vao;
		unsigned int _vbo;
		unsigned int _ebo;

		glm::vec3 _pos;
		block_t _type;
	};
}

#endif