#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "../main.h"

namespace game {
	class Block {
	public:
		Block();
		Block(int x, int y, int z, block_t type);
		~Block();

		static void loadTextures();
		static void setShader(Shader* shader);

		void setVals(int x, int y, int z, block_t type);

		glm::vec3 getPos() const;

		void update();
		void render();

	private:
		unsigned int _vao;
		unsigned int _vbo;
		unsigned int _ebo;

		static Shader* _shader;

		glm::vec3 _pos;
		block_t _type;

		static unsigned int _textures[TEXTURE_COUNT];
	};
}

#endif