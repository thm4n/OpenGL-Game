#version 330 core

layout (location = 0) in vec3 _pos;
layout (location = 1) in vec2 _tex;

out vec2 aTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(_pos, 1.0f);
	aTex = _tex;
}
