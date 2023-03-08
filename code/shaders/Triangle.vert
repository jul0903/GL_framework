#version 330
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec3 aPos;
uniform mat4 objMat;
uniform mat4 MVP_Mat;

out vec4 position;

void main() {
	position = MVP_Mat * objMat * vec4(aPos, 1.0);
}