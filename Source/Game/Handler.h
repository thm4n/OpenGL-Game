#ifndef _HANDLER_H_
#define _HANDLER_H_

#include "../main.h"
#include "../Objects/Object.h"
#include "../Objects/Player.h"

namespace game {
	class Player;

	class Handler {
	public:
		Handler();

		~Handler();

		Player* getPlayer();
		void setPlayer(Player*);
		
		std::vector<Object*> getObjects();
		std::vector<Object*> filterObjectsByType(obj_t type);

		void updateAll();
		void renderAll(glm::mat4 view, glm::mat4 projection);

		void inputUpdate(int key, int action);

	private:
		std::vector<Object*> _objects;
		Player* _player;
	};
}

#endif