#include "main.h" 

#include "ogl/ogl.h"
#include "Game/Game.h"
#include "./Dependencies/Paths_Defs.h"

int main() {
	game::Game* manager = nullptr;
	try {
		ogl::oglInit();
		manager = new game::Game();
		ogl::gladInit();

		textures::loadPathList("./Resources/Textures/");
		
		manager->generateViewports();
		manager->loadObjects();

		manager->beginGameLoop();
		
		delete manager;
		manager = nullptr;
	} catch (const std::exception& e) {
		std::cout << "Error Captured!\n" << e.what() << std::endl;
	}

	if(manager) 
		delete manager;
	
	ogl::oglTerminate();
	return 0;
}
