#include"Ex1c.h"

Ex1c::Ex1c(int width, int height) : Renderer(width, height)
{
	GLchar* vertex_shader_source[] = {
		"#version 330\n\
		 \n\
		 void main() {\n\
		 gl_Position = vec4(0.0,0.0,0.0,1.0);\n\
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

Ex1c::~Ex1c()
{
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &VAO);
}

GLuint Ex1c::CompileShader(GLchar* source, GLenum type, const char* name)
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

void Ex1c::linkProgram(GLuint program)
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

void Ex1c::render(float dt)
{
	glPointSize(40.0f);
	glBindVertexArray(VAO);
	glUseProgram(program);
	glDrawArrays(GL_POINTS, 0, 1);
}
