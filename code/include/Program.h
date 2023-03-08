#pragma once
#include<GL/glew.h>
#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

class Program
{
public:
	Program() {};
	Program(const char* name) {
		this->name = name;
		ID = glCreateProgram();
	};
	~Program() {
		glDeleteProgram(ID);
	};

	

	void CompileAndAttachShader(const char* shaderFilePath, GLenum shaderType, const char* shaderName) {
		//read from file
		std::string content;
		std::ifstream sahderInFile(shaderFilePath, std::ios::in);
		
		if (!sahderInFile.is_open()) {
			std::cout << "Error reading shader file: " << shaderName << std::endl;
			system("pause");
			exit(1);
		}

		std::string line = "";
		while (!sahderInFile.eof()) {
			std::getline(sahderInFile, line);
			content.append(line + "\n");
		}

		sahderInFile.close();
		std::cout << "'" << content << "'" << std::endl;

		//compile and attach
		shaders.emplace(shaderName, CompileShader(content.c_str(), shaderType, shaderName));
		LinkShader(shaderName);
	};

	GLuint getUniform(const char* name) {

	}

	void Use() {
		//if (ID > 0)
			glUseProgram(ID);
		//else
			//throw std::exception(std::string("Error when using program: " + std::string(name)).c_str());
	}

	void UnUse() {
		glUseProgram(0);
	}

	GLuint GetID() { return ID; }

	const char* GetName() { return name; }

private:
	void LinkShader(const char* name) {
		if (shaders.find(name) != shaders.end()) {
			glAttachShader(this->ID, shaders.at(name));
			LinkProgram(ID);
			glDeleteShader(shaders.at(name));
			shaders.erase(name);
			return;
		}
		std::cout << "Error: Unexisting shader " << name << std::endl;
		system("pause");
		exit(2);		
	};

	GLuint CompileShader(const char* shaderString, GLenum shaderType, const char* shaderName) {
		GLuint shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &shaderString, NULL);
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

	void LinkProgram(GLuint program)
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
	
	GLuint ID;
	const char* name;
	std::unordered_map<const char*, GLuint> shaders;
};
