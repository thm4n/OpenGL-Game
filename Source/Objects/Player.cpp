#include "Player.h"

namespace game {
	Player::Player() : Object() {
		this->_type = obj_t::_player;
		this->_shader = nullptr;
		this->_camera = nullptr;
	}

	Player::~Player() {
		
	}

	void Player::update() {
		this->_vel += this->_acc;
		this->_pos += this->_vel;
		this->_camera->_position = this->_pos;
		this->_camera->_position.y = this->_pos.y + 1;
	}
	
	void Player::render(glm::mat4 view, glm::mat4 projection) {
UNUSED(view);
UNUSED(projection);
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
