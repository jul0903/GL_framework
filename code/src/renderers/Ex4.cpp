#include "Ex4.h"

Ex4::Ex4(int width, int height) : Renderer(width, height)
{
	elapsedTime = 0.f;

	GLchar* vertex_shader_source[] = {
		"#version 330\n\
		layout (location = 0) in vec3 aPos;\n\
		uniform mat4 objMat;\n\
		void main() {\n\
			gl_Position = objMat * vec4(aPos, 1.0);\n\
		}"
	};
	GLchar* fragment_shader_source[] = {
		"#version 330\n\
		 \n\
		 out vec4 color;\n\
		 uniform vec4 aCol;\n\
		 \n\
		 void main() {\n\
			color = aCol;\n\
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

Ex4::~Ex4()
{
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

GLuint Ex4::CompileShader(GLchar* source, GLenum type, const char* name)
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

void Ex4::linkProgram(GLuint program)
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

void Ex4::render(float dt)
{
	elapsedTime += dt;
	glUseProgram(program);
	glBindVertexArray(VAO);
	float r = sin(elapsedTime);
	float g = -sin(elapsedTime);
	float b = cos(elapsedTime / 2);;
	glUniform4f(glGetUniformLocation(program, "aCol"), r, g, b, 1.0f);

	float size = 0.5f;
	glm::mat4 s = glm::scale(glm::mat4(), glm::vec3(size, size, size));
	
	glm::mat4 tr = glm::translate(glm::mat4(), glm::vec3(0.f, 0.5f, 0.f) * sin(elapsedTime));

	glm::mat4 rot = glm::rotate(glm::mat4(), glm::radians(90.f), glm::vec3(0.f, 0.f, 1));

	glm::mat4 objMat = tr * rot * s;
	glUniformMatrix4fv(glGetUniformLocation(program, "objMat"), 1, GL_FALSE, glm::value_ptr(objMat));

	glDrawArrays(GL_TRIANGLES, 0, 3);
}