#pragma once
#include "Renderer.h"

class Ex2_triangleVBO : public Renderer
{
public:
	Ex2_triangleVBO(int width, int height);
	~Ex2_triangleVBO();

private:
	float vertices[12] = {
		-0.5f, -0.5f, 0.f,
		0.5f, -0.5f, 0.f,
		0.0f, 0.5f, 0.f,
	};

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

