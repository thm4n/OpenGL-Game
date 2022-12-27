#include "Camera.h"

namespace game {
	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
		this->_front            = glm::normalize(glm::vec3(1.0f, 0.0f, -3.0f));
		this->_mouseSensitivity = SENSITIVITY;
		this->_zoom             = ZOOM;
		this->_position         = position;
		this->_worldUp          = up;
		this->_yaw              = yaw;
		this->_pitch            = pitch;

		updateCameraVectors();
	}

	glm::mat4 Camera::getViewMatrix() {
		return glm::lookAt(_position, _position + _front, _up);
	}

	void Camera::update_position(glm::vec3 playerPos) {
		this->_position = playerPos;
	}

	void Camera::ProcessMouseMovement(glm::vec2 offset) {
		offset *= _mouseSensitivity;

		_yaw   -= offset.x;
		_pitch += offset.y;

		if (_pitch > 89.0f)
			_pitch = 89.0f;
		if (_pitch < -89.0f)
			_pitch = -89.0f;

		updateCameraVectors();
	}

	void Camera::processFOVCalibration(float yoffset) {
		_zoom -= (float)yoffset;
		if (_zoom < 1.0f)
			_zoom = 1.0f;
		if (_zoom > 45.0f)
			_zoom = 45.0f;
	}

	void Camera::updateCameraVectors() {
		// calculate the new _front vector
		glm::vec3 front;
		front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		front.y = sin(glm::radians(_pitch));
		front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		_front = glm::normalize(front);
		// also re-calculate the _right and _up vector
		_right = glm::normalize(glm::cross(_front, _worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		_up    = glm::normalize(glm::cross(_right, _front));
	}
}
