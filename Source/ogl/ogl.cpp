#include "ogl.h"

namespace ogl {
	void oglInit() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	void oglTerminate() {
		glfwTerminate();
	}
	
	void gladInit() {
		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			throw Exception(Exception::graphics_error, "Failed to initialize GLAD");
		}
	}
}
