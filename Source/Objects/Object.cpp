#include "Object.h"

namespace game {
	Object::Object() {
		this->_pos = glm::vec3(0);
		this->_vel = glm::vec3(0);
		this->_acc = glm::vec3(0);
		this->_type = obj_t::_void;
	}

	Object::~Object() {
		if(this->_shader)
			delete this->_shader;
		glDeleteVertexArrays(1, &this->_vao);
		glDeleteBuffers(1, &this->_vbo);
		glDeleteBuffers(1, &this->_ebo);
	}

	glm::vec3 Object::clamp(const glm::vec3& val, const glm::vec3 min, const glm::vec3 max) {
		glm::vec3 vec = glm::vec3(0);
		
		if(val.x < min.x) vec.x = min.x;
		if(val.x > max.x) vec.x = max.x;

		if(val.y < min.y) vec.y = min.y;
		if(val.y > max.y) vec.y = max.y;

		if(val.z < min.z) vec.z = min.z;
		if(val.z > max.z) vec.z = max.z;

		return vec;
	}

	glm::vec2 Object::clamp(const glm::vec2& val, const glm::vec2 min, const glm::vec2 max) {
		glm::vec2 vec = val;
		
		if(val.x < min.x) vec.x = min.x;
		if(val.x > max.x) vec.x = max.x;

		if(val.y < min.y) vec.y = min.y;
		if(val.y > max.y) vec.y = max.y;

		return vec;
	}

	glm::vec3 Object::getPosition() const{
		return this->_pos;
	}

	glm::vec3 Object::getVelocity() const {
		return this->_vel;
	}

	glm::vec3 Object::getAcc() const {
		return this->_vel;
	}

	obj_t Object::getType() const {
		return this->_type;
	}

	void Object::setPosition(glm::vec3 pos) {
		this->_pos = pos;
	}

	void Object::setVelocity(glm::vec3 vel) {
		this->_vel = vel;
	}

	void Object::setAcc(glm::vec3 acc) {
		this->_acc = acc;
	}
}
