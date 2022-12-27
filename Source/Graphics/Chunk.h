#ifndef _CHUNK_H_
#define _CHUNK_H_

#include "../main.h"
#include "Block.h"

namespace game {
	class Chunk {
	public:
		Chunk(int x, int y);
		~Chunk();

		void loadShaders();
		void loadResources();

		void update();
		void render(glm::mat4 view, glm::mat4 projection);

	private:
		Shader* _shader;

		glm::vec2 _pos;

		unsigned int _vao;
		unsigned int _vbo;
		unsigned int _ebo;
	
		glm::mat4 _model;

		Block* _blocks[CHUNK_SIZE][Y_MAX][CHUNK_SIZE];
	
		unsigned int _textures[TEXTURE_COUNT];
	};
}

#endif