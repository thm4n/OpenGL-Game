#ifndef _CHUNK_H_
#define _CHUNK_H_

#include "../main.h"
#include "Block.h"

namespace game {
	class Chunk {
	public:
		Chunk(int x, int y);
		~Chunk();

		static void setShader(Shader* shader);

		void update();
		void render();

	private:
		glm::vec2 _pos;

		static Shader* _shader;

		Block* _blocks[CHUNK_SIZE][Y_MAX][CHUNK_SIZE];
	};
}

#endif