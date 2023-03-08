#pragma once
#include "Renderer.h"

class Ex2_triangle : public Renderer
{
public:
	Ex2_triangle(int width, int height);
	~Ex2_triangle();

private:
	GLuint CompileShader(GLchar* source, GLenum type, const char* name = "");
	void linkProgram(GLuint program);

protected:
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program;

	GLuint VAO;

	void render(float dt) override;
};

