/*
 * SaloonShader.h
 *
 *  Created on: Apr 16, 2014
 *      Author: james
 */

#ifndef SALOONSHADER_H_
#define SALOONSHADER_H_

#include "Saloon.h"
#include "Transform.h"

class SaloonShader {
private:
	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint _program;
	GLuint _shaders[NUM_SHADERS];
	GLuint _uniforms[NUM_UNIFORMS];

public:
	SaloonShader();
	virtual ~SaloonShader();

	void load(const string& fileName);
	void bind();
	void update(const Transform& transform);
	void unbind();
};

#endif /* SALOONSHADER_H_ */
