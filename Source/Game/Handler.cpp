#include "Handler.h" 

namespace game {
	Handler::Handler() {
		
	}

	Handler::~Handler() {
		for(size_t i = 0; i < this->_objects.size(); i++)
			delete this->_objects[i];
		if(this->_player)
			delete this->_player;
	}

	Player* Handler::getPlayer() {
		return this->_player;
	}
	
	void Handler::setPlayer(Player* player) {
		this->_player = player;
	}

	std::vector<Object*> Handler::filterObjectsByType(obj_t type) {
		std::vector<Object*> objects;
		for(size_t i =0; i < this->_objects.size(); i++)
			if(this->_objects[i]->getType() == type)
				objects.push_back(this->_objects[i]);
		return objects;
	}

	void Handler::updateAll() {
		for(size_t i = 0; i < this->_objects.size(); i++) {
			this->_objects[i]->update();
		}
		this->_player->update();
	}

	void Handler::renderAll(glm::mat4 view, glm::mat4 projection) {
		for(size_t i = 0; i < this->_objects.size(); i++) {
			this->_objects[i]->render(view, projection);
		}
		this->_player->render(view, projection);
	}

	void Handler::inputUpdate(int key, int action) {
		this->_player->inputUpdate(key, action);
	}
}
