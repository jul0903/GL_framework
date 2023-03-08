#include "Ex2_triangle.h"

Ex2_triangle::Ex2_triangle(int width, int height) : Renderer(width, height)
{
	GLchar* vertex_shader_source[] = {
		"#version 330\n\
		void main() {\n\
			const vec4 vertices[3] = vec4[3](\n\
			vec4(0.25, -0.25, 0.5, 1.0),\n\
			vec4(-0.25, -0.25, 0.5, 1.0),\n\
			vec4(0.25, 0.25, 0.5, 1.0));\n\
			gl_Position = vertices[gl_VertexID];\n\
		}"
	};
	GLchar* fragment_shader_source[] = {
		"#version 330\n\
		 \n\
		 out vec4 color;\n\
		 \n\
		 void main() {\n\
		 color = vec4(0.0,0.8,1.0,1.0);\n\
		}"
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	vertex_shader = CompileShader(vertex_shader_source[0], GL_VERTEX_SHADER);

	fragment_shader = CompileShader(fragment_shader_source[0], GL_FRAGMENT_SHADER);

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	linkProgram(program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glBindVertexArray(0);
}

Ex2_triangle::~Ex2_triangle()
{
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &VAO);
}

GLuint Ex2_triangle::CompileShader(GLchar* source, GLenum type, const char* name)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	GLint res;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE) {
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &res);
		char* buff = new char[res];
		glGetShaderInfoLog(shader, res, &res, buff);
		fprintf(stderr, "Error Shader %s: %s", name, buff);
		delete[] buff;
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}

void Ex2_triangle::linkProgram(GLuint program)
{
	glLinkProgram(program);
	GLint res;
	glGetProgramiv(program, GL_LINK_STATUS, &res);
	if (res == GL_FALSE) {
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &res);
		char* buff = new char[res];
		glGetProgramInfoLog(program, res, &res, buff);
		fprintf(stderr, "Error Link: %s", buff);
		delete[] buff;
	}
}

void Ex2_triangle::render(float dt)
{
	glBindVertexArray(VAO);
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
