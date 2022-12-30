#ifndef _GAME_H_
#define _GAME_H_

#include "../main.h"

#include "Handler.h"
#include "Camera.h"

#include "../Objects/Object.h"
#include "../Objects/Player.h"

#include "../Graphics/Map.h"
#include "../Graphics/Chunk.h"
#include "../Graphics/Block.h"

namespace game {
	class Handler;
	class Camera;

	class Game {
	public:
		Game();
		~Game();

		void generateViewports();

		void beginGameLoop();

		void processInput();
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
		static void mouseMovementCallback(GLFWwindow* window, double x, double y);

		void loadObjects();

		GLFWwindow* _window;
		
	private:
		glm::ivec2 _winDims;

		Map* _map;

		static Camera* _camera;
		static Handler* _handler;
		static glm::vec2 _prev_mouse_position;
	};
}

#endif