#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "../main.h"

namespace game {
	class Block {
	public:
		Block(int x, int y, int z, block_t type);
		~Block();

		void loadShader();
		void loadResources();

		void update();
		void render(glm::mat4 view, glm::mat4 projection);

	private:
		Shader* _shader;
		
		unsigned int _vao;
		unsigned int _vbo;
		unsigned int _ebo;

		glm::vec3 _pos;
		block_t _type;

		//temporary:
		unsigned int _texture;
	};
}

#endif