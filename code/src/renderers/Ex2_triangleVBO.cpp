#include "Ex2_triangleVBO.h"

Ex2_triangleVBO::Ex2_triangleVBO(int width, int height) : Renderer(width, height)
{
	GLchar* vertex_shader_source[] = {
		"#version 330\n\
		layout (location = 0) in vec3 aPos;\n\
		void main() {\n\
			gl_Position = vec4(aPos, 1.0);\n\
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

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(
		GL_ARRAY_BUFFER,//type
		sizeof(vertices),//size of the data
		vertices, //The data
		GL_STATIC_DRAW);//Hint

	glVertexAttribPointer(
		0,	//location of the attribute (same as for the shader)
		3,	//size of the attribute (3 coords)
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(float), //space between consecutive vertex attributes
		(void*)0	//offset of where the position data begins in the buffer
	);

	glEnableVertexAttribArray(0);	//0 is the location of the attribute

	vertex_shader = CompileShader(vertex_shader_source[0], GL_VERTEX_SHADER, "Vertex Shader");

	fragment_shader = CompileShader(fragment_shader_source[0], GL_FRAGMENT_SHADER, "Fragment Shader");

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	linkProgram(program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glBindVertexArray(0);
}

Ex2_triangleVBO::~Ex2_triangleVBO()
{
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

GLuint Ex2_triangleVBO::CompileShader(GLchar* source, GLenum type, const char* name)
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

void Ex2_triangleVBO::linkProgram(GLuint program)
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

void Ex2_triangleVBO::render(float dt)
{
	glUseProgram(program);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
