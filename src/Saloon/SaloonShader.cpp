/*
 * SaloonShader.cpp
 *
 *  Created on: Apr 16, 2014
 *      Author: james
 */

#include "SaloonShader.h"
#include <glm/glm.hpp>

SaloonShader::SaloonShader() :
	_program(0)
{
	for(uint i = 0; i < NUM_SHADERS; i++) {
		_shaders[i] = 0;
	}
}

SaloonShader::~SaloonShader() {

	if(_program != 0) {
		for(uint i = 0; i < NUM_SHADERS; i++) {
			if(_shaders[i] != 0) {
				glDetachShader(_program, _shaders[i]);
				glDeleteShader(_shaders[i]);
			}
		}

		glDeleteProgram(_program);
	}
}

void SaloonShader::load(const string& fileName) {
	_program = glCreateProgram();

	_shaders[0] = glCreateShaderFromText(readTextFile(fileName + ".vs"), GL_VERTEX_SHADER);
	_shaders[1] = glCreateShaderFromText(readTextFile(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for(uint i = 0; i < NUM_SHADERS; i++) {
		glAttachShader(_program, _shaders[i]);
	}

	glBindAttribLocation(_program, 0, "position");
	glBindAttribLocation(_program, 1, "texCoord");

	glLinkProgram(_program);
	glCheckShaderError(_program, GL_LINK_STATUS, true, "Program Linking Failed");

	glValidateProgram(_program);
	glCheckShaderError(_program, GL_VALIDATE_STATUS, true, "Program Validation Failed");

	_uniforms[TRANSFORM_U] = glGetUniformLocation(_program, "transform");

}

void SaloonShader::bind() {
	glUseProgram(_program);
}

void SaloonShader::update(const Transform& transform) {
	glm::mat4 model = transform.getModel();

	glUniformMatrix4fv(_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

void SaloonShader::unbind() {
	glUseProgram(0);
}
