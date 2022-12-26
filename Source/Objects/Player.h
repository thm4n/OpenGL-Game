#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "../main.h"
#include "Object.h"
#include "../Game/Camera.h"

namespace game {
	class Camera;
	
	class Player : public Object {
	public:
		Player();
		~Player();

		virtual void update();
		virtual void render(glm::mat4 view, glm::mat4 projection);
	
		void inputUpdate(int key, int action);

		void setCamera(Camera* camera);

	private:
		Camera* _camera;
	};
}

#endif