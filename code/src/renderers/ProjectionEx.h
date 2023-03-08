#pragma once
#include "Renderer.h"
#include "Program.h"

class ProjectionEx : public Renderer
{
public:
	ProjectionEx(int width, int height);
	~ProjectionEx();

private:
	float vertices[12] = {
		-0.5f, -0.5f, 0.f,
		0.5f, -0.5f, 0.f,
		0.0f, 0.5f, 0.f,
	};
	float elapsedTime;

protected:
	/*GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program;*/
	Program mainProgram;

	GLuint VAO;
	GLuint VBO;

	void render(float dt) override;
};

