#ifndef _CAMERA_H
#define _CAMERA_H

#include "../main.h"
#include "Game.h"

// Default camera values
namespace game {
	const float YAW         = -90.0f;
	const float PITCH       =  0.0f;
	const float SENSITIVITY =  0.01f;
	const float ZOOM        =  45.0f;

	class Camera {
	public:
		Camera(glm::vec3 position, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

		glm::mat4 getViewMatrix();

		void update_position(glm::vec3 playerPos);
		void ProcessMouseMovement(glm::vec2 offset);
		void processFOVCalibration(float yoffset);

		// camera Attributes
		glm::vec3 _position;
		glm::vec3 _front;
		glm::vec3 _up;
		glm::vec3 _right;
		glm::vec3 _worldUp;

		// euler Angles
		float _yaw;   //up-down
		float _pitch; //left-right

		// camera options
		float _mouseSensitivity;
		float _zoom;

	private:
		void updateCameraVectors();
	};
}

#endif