#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "../main.h"
#include "../Graphics/Map.h"

namespace game {
	class Object {
	public:
		Object();
		virtual ~Object();

		virtual void update() = 0;
		virtual void render(glm::mat4 view, glm::mat4 projection) = 0;

		static glm::vec2 clamp(const glm::vec2& val, const glm::vec2 min, const glm::vec2 max);
		static glm::vec3 clamp(const glm::vec3& val, const glm::vec3 min, const glm::vec3 max);

		glm::vec3 getPosition() const;
		glm::vec3 getVelocity() const;
		glm::vec3 getAcc() const;
		obj_t getType() const;

		void setPosition(glm::vec3 pos);
		void setVelocity(glm::vec3 vel);
		void setAcc(glm::vec3 acc);

	protected:
		Shader* _shader;
		
		unsigned int _vao;
		unsigned int _vbo;
		unsigned int _ebo;

		glm::vec3 _pos;
		glm::vec3 _vel;
		glm::vec3 _acc;
		
		double _yaw;
		double _pitch;

		obj_t _type;
	};
}

#endif