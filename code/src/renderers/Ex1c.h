#pragma once
#include "Renderer.h"
class Ex1c : public Renderer
{
public:
	Ex1c(int width, int height);
	~Ex1c();

private:
	GLuint CompileShader(GLchar* source, GLenum type, const char* name="");
	void linkProgram(GLuint program);

protected:
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program;

	GLuint VAO;
	//GLuint VBO;

	//void Init();
	void render(float dt) override;
};

