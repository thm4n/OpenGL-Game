#include "Player.h"

namespace game {
	Player::Player() : Object() {
		this->_type = obj_t::_player;
		this->_shader = nullptr;
		this->_camera = nullptr;

		float vertices[] = {
			-PLUS_ARM_WID, -PLUS_ARM_LEN,
			+PLUS_ARM_WID, -PLUS_ARM_LEN,

			-PLUS_ARM_WID, +PLUS_ARM_LEN,
			+PLUS_ARM_WID, +PLUS_ARM_LEN,

			-PLUS_ARM_LEN, -PLUS_ARM_WID,
			-PLUS_ARM_LEN, +PLUS_ARM_WID,
			
			+PLUS_ARM_LEN, -PLUS_ARM_WID,
			+PLUS_ARM_LEN, +PLUS_ARM_WID,
		};

		for(size_t i = 1; i < sizeof(vertices) / sizeof(float); i += 2) {
			vertices[i - 1] *= (2 / WINDOW_BASE_WIDTH);
			
			vertices[i]     *= (2 / WINDOW_BASE_HEIGHT);
		}

		unsigned int indices[] {
			0,1,3,
			0,2,3,

			4,5,7,
			4,6,7
		};

		glGenVertexArrays(1, &this->_vao);
		glGenBuffers(1, &this->_vbo);
		glGenBuffers(1, &this->_ebo);

		glBindVertexArray(this->_vao);

		glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	Player::~Player() {
		
	}

	void Player::loadShader() {
		this->_shader = new Shader("Player.vs", "Player.fs");
	}

	void Player::update() {
		Block* temp = Map::getFirstBlockBelowPos(this->_pos);
		int y_min = 0;
		if(temp != nullptr) {
			glm::vec3 pos = temp->getPos();
			printf("Block position: (%.2f, %.2f, %.2f)\n", pos.x, pos.y, pos.z);
			y_min = temp->getPos().y;
		}
		
		this->_pos += this->_vel;
		this->_vel += this->_acc;
		
		this->_pos.y = this->_pos.y > y_min ? this->_pos.y : y_min;

		this->_camera->_position = this->_pos;
		this->_camera->_position.y = this->_pos.y + 1;

		printf("Player position: (%.2f, %.2f, %.2f)\n", this->_pos.x, this->_pos.y, this->_pos.z);
	}
	
	void Player::render(glm::mat4 view, glm::mat4 projection) {
UNUSED(view);
UNUSED(projection);

		this->_shader->use();

		glEnable(GL_BLEND);

		glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
		glBindVertexArray(this->_vao);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

		glDisable(GL_BLEND);
	}

	void Player::inputUpdate(int key, int action) {
		float toggle = action == GLFW_PRESS ? 1.00f : 0.00f;
		glm::vec3 mod_front = this->_camera->_front;
		mod_front.y = 0;

		switch(key) {
		case GLFW_KEY_W:
			this->_vel =  mod_front * (PLAYER_BASE_SPEED * toggle);
			break;
		case GLFW_KEY_S:
			this->_vel = -mod_front * (PLAYER_BASE_SPEED * toggle);
			break;
		case GLFW_KEY_D:
			this->_vel =  this->_camera->_right * (PLAYER_BASE_SPEED * toggle);
			break;
		case GLFW_KEY_A:
			this->_vel = -this->_camera->_right * (PLAYER_BASE_SPEED * toggle);
			break;
		case GLFW_KEY_LEFT_SHIFT:
			this->_vel.y = -this->_camera->_up.y * (PLAYER_BASE_SPEED * toggle);
			break;
		case GLFW_KEY_SPACE:
			this->_vel.y = this->_camera->_up.y * (PLAYER_BASE_SPEED * toggle);
			break;
		}
	}
	
	void Player::setCamera(Camera* camera) {
		this->_camera = camera;
	}
}
