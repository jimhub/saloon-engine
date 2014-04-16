/*
 * SaloonTexture.h
 *
 *  Created on: Apr 15, 2014
 *      Author: james
 */

#ifndef SALOONTEXTURE_H_
#define SALOONTEXTURE_H_

#include "glHelpers.h"

class SaloonTexture {
private:
	GLuint _texture;

	GLuint* _pixels;
	GLuint _texWidth, _texHeight;

public:
	SaloonTexture(const char* fileName, GLuint filterMode=GL_NEAREST);
	virtual ~SaloonTexture();

	bool lock();
	bool unlock();

	void freeTexture();

	GLuint getPixel(GLuint x, GLuint y) const;

	void setPixel(GLuint x, GLuint y, GLuint pixel);

	void render(GLfloat x, GLfloat y) const;

	GLuint* getPixels() const {
		return _pixels;
	}

	GLuint getHeight() const {
		return _texHeight;
	}

	GLuint getTexture() const {
		return _texture;
	}

	GLuint getWidth() const {
		return _texWidth;
	}
};

#endif /* SALOONTEXTURE_H_ */
