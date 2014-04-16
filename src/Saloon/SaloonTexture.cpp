/*
 * SaloonTexture.cpp
 *
 *  Created on: Apr 15, 2014
 *      Author: james
 */

#include "SaloonTexture.h"

SaloonTexture::SaloonTexture(const char* fileName, GLuint filterMode) {
	_texture = glLoadTexture(fileName, _texWidth, _texHeight, filterMode);
	_pixels = NULL;
}

SaloonTexture::~SaloonTexture() {
	freeTexture();
}

bool SaloonTexture::lock() {
	if(_pixels == NULL && _texture != 0) {
		GLuint size = _texWidth * _texHeight;
		_pixels = new GLuint[size];

		glBindTexture(GL_TEXTURE_2D, _texture);

		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, _pixels);

		glBindTexture(GL_TEXTURE_2D, 0);

		return true;
	}

	return false;
}

bool SaloonTexture::unlock() {
	if( _pixels != NULL && _texture != 0 )
	{
		//Set current texture
		glBindTexture( GL_TEXTURE_2D, _texture );

		//Update texture
		glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, _texWidth, _texHeight,
				GL_RGBA, GL_UNSIGNED_BYTE, _pixels );

		//Delete pixels
		delete[] _pixels;
		_pixels = NULL;

		//Unbind texture
		glBindTexture( GL_TEXTURE_2D, NULL );

		return true;
	}

	return false;
}

GLuint SaloonTexture::getPixel(GLuint x, GLuint y) const {
	return _pixels[ y * _texWidth + x ];
}

void SaloonTexture::freeTexture() {
	if(_texture != 0) {
		glDeleteTextures(1, &_texture);
		_texture = 0;
	}

	if(_pixels != NULL) {
		delete[] _pixels;
		_pixels = NULL;
	}

	_texWidth = 0;
	_texHeight = 0;
}

void SaloonTexture::setPixel(GLuint x, GLuint y, GLuint pixel) {
	_pixels[ y * _texWidth + x ] = pixel;
}

void SaloonTexture::render(GLfloat x, GLfloat y) const {
	glDrawTexture(_texture, x, y, _texWidth, _texHeight);
}
