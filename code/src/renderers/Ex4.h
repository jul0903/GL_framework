#pragma once
#include "Renderer.h"
class Ex4 : public Renderer
{
public:
	Ex4(int width, int height);
	~Ex4();

private:
	float vertices[12] = {
		-0.5f, -0.5f, 0.f,
		0.5f, -0.5f, 0.f,
		0.0f, 0.5f, 0.f,
	};
	float elapsedTime;

	GLuint CompileShader(GLchar* source, GLenum type, const char* name = "");
	void linkProgram(GLuint program);

protected:
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program;

	GLuint VAO;
	GLuint VBO;

	void render(float dt) override;
};

