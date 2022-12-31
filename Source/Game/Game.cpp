#include "Game.h"

namespace game {
	Handler* Game::_handler = nullptr;
	Camera* Game::_camera = nullptr;
	glm::vec2 Game::_prev_mouse_position;

	Game::Game() {
		this->_window = glfwCreateWindow(WINDOW_BASE_WIDTH, WINDOW_BASE_HEIGHT, "Game", NULL, NULL);
		if(!this->_window) {
			throw Exception(Exception::graphics_error, "Failed to create GLFW window.");
		}
		glfwMakeContextCurrent(this->_window);
		glfwGetFramebufferSize(this->_window, &this->_winDims.x, &this->_winDims.y);
		glfwSwapInterval(0);

		glfwSetInputMode(this->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwSetKeyCallback(this->_window, this->keyCallback);
		glfwSetScrollCallback(this->_window, this->scrollCallback);
		glfwSetMouseButtonCallback(this->_window, this->mouseCallback);
		glfwSetCursorPosCallback(this->_window, this->mouseMovementCallback);

		Game::_prev_mouse_position = glm::vec2(WINDOW_BASE_WIDTH, WINDOW_BASE_HEIGHT) * 0.5f;

		stbi_set_flip_vertically_on_load(true);

		this->_map = new Map();
	}

	Game::~Game() {
		glfwDestroyWindow(this->_window);
		delete this->_map;
		delete Game::_handler;
		delete Game::_camera;
	}

	void Game::generateViewports() {
		glViewport(0, 0, this->_winDims.x, this->_winDims.y); //game viewport
	}

	void Game::beginGameLoop() {
		glm::mat4 view;
		glm::mat4 projection;

		glEnable(GL_DEPTH_TEST);

		std::chrono::high_resolution_clock::time_point 
							nowTime,
							lastTime = std::chrono::high_resolution_clock::now(),
							timer = lastTime;
		double ns = 1000000000.0f / FPS_CAP;
		double delta = 0.0f;

		size_t frames = 0, updates = 0;

		this->_map->loadShaders();
		this->_map->loadResources();

		this->_map->loadMap();

		while(!glfwWindowShouldClose(this->_window)) {
			nowTime = std::chrono::high_resolution_clock::now();
			delta +=  (std::chrono::nanoseconds(nowTime - lastTime)).count() / ns;
			lastTime = nowTime;

			this->processInput();

			glClearColor(WINDOW_CLEAR_COLOR);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//matrix game
			projection = glm::perspective(glm::radians(this->_camera->_zoom), (float)WH_RATIO, 0.1f, 100.0f);
			view = this->_camera->getViewMatrix();

			//update
			while(delta >= 1.00f) {
				this->_handler->updateAll();
				this->_map->update();
				updates++;
				delta--;
			}

			//render
			this->_handler->renderAll(view, projection);
			this->_map->render(view, projection);
			frames++;

			glfwSwapBuffers(this->_window);
			glfwPollEvents();

			if(std::chrono::nanoseconds(std::chrono::high_resolution_clock::now() - timer) > std::chrono::seconds(1)) {
				timer += std::chrono::seconds(1);
				printf("fpsaaaaaa: %ld\nups: %ld\n\n", frames, updates);
				frames = 0;
				updates = 0;
			}
		}
	}

	void Game::processInput() {

	}

	void Game::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		UNUSED(window);
		UNUSED(scancode);
		UNUSED(mods);

		if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, true);

		Game::_handler->inputUpdate(key, action);
	}

	void Game::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
		UNUSED(window);
		UNUSED(xoffset);
		UNUSED(yoffset);
	}

	void Game::mouseCallback(GLFWwindow* window, int button, int action, int mods) {
		UNUSED(window);
		UNUSED(button);
		UNUSED(action);
		UNUSED(mods);
	}

	void Game::mouseMovementCallback(GLFWwindow* window, double x, double y) {
		UNUSED(window);

		glm::vec2 offset = Game::_prev_mouse_position - glm::vec2(x,y);
		Game::_prev_mouse_position = glm::vec2(x,y);
		Game::_camera->ProcessMouseMovement(offset);
	}

	void Game::loadObjects() {
		Player* player = new Player();
		Game::_handler = new Handler();
		this->_handler->setPlayer(player);
		Game::_camera = new Camera(this->_handler->getPlayer()->getPosition());
		player->setCamera(Game::_camera);

		player->loadShader();
	}
}
