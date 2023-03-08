#include "ProjectionEx.h"

ProjectionEx::ProjectionEx(int width, int height) : Renderer(width, height)
{
	elapsedTime = 0.f;

	/*GLchar* vertex_shader_source[] = {
		"#version 330\n\
		layout (location = 0) in vec3 aPos;\n\
		uniform mat4 objMat;\n\
		uniform mat4 MVP_Mat;\n\
		void main() {\n\
			gl_Position = MVP_Mat * objMat * vec4(aPos, 1.0);\n\
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
	};*/

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

	mainProgram = Program("Triangles program");
	mainProgram.CompileAndAttachShader("../../shaders/Triangle.vert", GL_VERTEX_SHADER, "Triangle VS");
	mainProgram.CompileAndAttachShader("../../shaders/Triangle.frag", GL_FRAGMENT_SHADER, "Triangle FS");
	//vertex_shader = CompileShader(vertex_shader_source[0], GL_VERTEX_SHADER, "Vertex Shader");
	//fragment_shader = CompileShader(fragment_shader_source[0], GL_FRAGMENT_SHADER, "Fragment Shader");

	//glAttachShader(program, vertex_shader);
	//glAttachShader(program, fragment_shader);
	///linkProgram(program);

	//glDeleteShader(vertex_shader);
	//glDeleteShader(fragment_shader);
	glBindVertexArray(0);
}

ProjectionEx::~ProjectionEx()
{
	//glDeleteProgram(program);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}


void ProjectionEx::render(float dt)
{
	elapsedTime += dt;
	//glUseProgram(program);
	mainProgram.Use();
	glBindVertexArray(VAO);

	//Render primary vars sent to shader
		//MVP
	glUniformMatrix4fv(glGetUniformLocation(mainProgram.GetID(), "MVP_Mat"), 1, GL_FALSE, glm::value_ptr(_MVP));

	//Object transformation - RED TRIANGLE (CENTRE)
	float size = 1.f;
	glm::mat4 scaleM = glm::scale(glm::mat4(), glm::vec3(size, size, size));

		//Rotate on axis X -55 deg
	glm::mat4 rotationM = glm::rotate(glm::mat4(), glm::radians(-55.f), glm::vec3(1.f, 0.f, 0.f));

	glm::mat4 translationM = glm::translate(glm::mat4(), glm::vec3(0.f, 0.0f, -10.f));

		//Set objMat as Uniform
	glm::mat4 objMat = translationM * rotationM * scaleM;
	glUniformMatrix4fv(glGetUniformLocation(mainProgram.GetID(), "objMat"), 1, GL_FALSE, glm::value_ptr(objMat));

	
	//set color through uniform
	glUniform4f(glGetUniformLocation(mainProgram.GetID(), "aCol"), 150.f, 0.f, 0.f, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	

	//Object transformation - PINK TRIANGLE (RIGHT)
	size = 1.f;
	scaleM = glm::scale(glm::mat4(), glm::vec3(size, size, size));

		//Rotate on axis Y 45 deg
	rotationM = glm::rotate(glm::mat4(), glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f));

	translationM = glm::translate(glm::mat4(), glm::vec3(3.f, 0.0f, -10.f));

		//Set objMat as Uniform
	objMat = translationM * rotationM * scaleM;
	glUniformMatrix4fv(glGetUniformLocation(mainProgram.GetID(), "objMat"), 1, GL_FALSE, glm::value_ptr(objMat));

	
	//set color through uniform
	glUniform4f(glGetUniformLocation(mainProgram.GetID(), "aCol"), 1.f, 0.321f, 0.945f, 1.f);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	
	//Object transformation - BLUE TRIANGLE (LEFT)
	size = 1.f;
	scaleM = glm::scale(glm::mat4(), glm::vec3(size, size, size));

		//Rotate on axis Y 45 deg
	rotationM = glm::rotate(glm::mat4(), glm::radians(180.f), glm::vec3(0.f, 0.f, 1.f));
	rotationM = glm::rotate(rotationM, glm::radians(-40.f), glm::vec3(0.f, 1.f, 0.f));

	translationM = glm::translate(glm::mat4(), glm::vec3(-3.f, 0.0f, -10.f));

		//Set objMat as Uniform
	objMat = translationM * rotationM * scaleM;
	glUniformMatrix4fv(glGetUniformLocation(mainProgram.GetID(), "objMat"), 1, GL_FALSE, glm::value_ptr(objMat));

	
	//set color through uniform
	glUniform4f(glGetUniformLocation(mainProgram.GetID(), "aCol"), 0.321f, 1.f, 0.901f, 1.f);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}
