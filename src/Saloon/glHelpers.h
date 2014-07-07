/*
 * glHelpers.h
 *
 *  Created on: Feb 23, 2014
 *      Author: james
 */

#ifndef GLHELPERS_H_
#define GLHELPERS_H_

#define GL_GLEXT_PROTOTYPES

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl.h>

#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#else
#include <GL/gl.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

#define TWO_PI 6.283185307f
#define PI 3.141592654f

struct GLRect {
	GLint x, y, w, h;

	GLRect() : x(0), y(0), w(0), h(0) {}

	GLRect(GLint x, GLint y, GLint w, GLint h) :
		x(x), y(y), w(w), h(h) {}
};

struct GLRectF {
	GLfloat x, y, w, h;

	GLRectF() : x(0), y(0), w(0), h(0) {}

	GLRectF(GLfloat x, GLfloat y, GLfloat w, GLfloat h) :
		x(x), y(y), w(w), h(h) {}
};

struct GLColor4 {
	GLfloat r, g, b, a;

	GLColor4() : r(1), g(1), b(1), a(1) {}

	GLColor4(GLfloat r, GLfloat g, GLfloat b, GLfloat a) :
		r(r), g(g), b(b), a(a) {}
};

struct GLStyle {
	GLColor4 fillColor, strokeColor;
	bool fillOn, strokeOn;
	GLfloat strokeWidth;

	GLStyle() : fillOn(true), strokeOn(false), strokeWidth(1.0f) {}

	GLStyle(const GLStyle& copyStyle) {
		fillColor = copyStyle.fillColor;
		strokeColor = copyStyle.strokeColor;

		fillOn = copyStyle.fillOn;
		strokeOn = copyStyle.strokeOn;

		strokeWidth = copyStyle.strokeWidth;
	}
};

void glInit(int screenWidth, int screenHeight);
void glDestroy();

GLuint glCreateRenderTarget(GLuint* tex, GLuint width, GLuint height, GLuint filterMode=GL_NEAREST);
void glActivateRenderTarget(GLuint FBO, GLuint width, GLuint height);
void glDeactivateRenderTarget();

void glColor4(const GLColor4& color);

GLuint glLoadTexture(const char* fileName, GLuint filterMode=GL_NEAREST);
GLuint glLoadTexture(const char* fileName, GLuint& width, GLuint& height, GLuint filterMode=GL_NEAREST);

void glDrawTexture(GLuint texture, GLfloat x, GLfloat y, GLfloat w, GLfloat h,
		GLfloat clipX=0, GLfloat clipY=0, GLfloat clipX1=1, GLfloat clipY1=1);
void glDrawTexture(GLuint texture, GLfloat x, GLfloat y, GLfloat w, GLfloat h, const GLRectF &clip);
void glDrawTexture(GLuint texture, const GLRectF &quad, const GLRectF &clip);

void glDrawLine(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1);
void glDrawRect(const GLRectF& rect);
void glDrawRect(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1);
void glDrawCircle(GLfloat cx, GLfloat cy, GLfloat radius);
void glDrawPoly(GLfloat verts[], int numVerts);

void glSetFill(bool fillOn);
void glSetAlpha(GLfloat a);
void glSetColor(GLfloat r, GLfloat g, GLfloat b);
void glSetColorA(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

void glSetStroke(bool strokeOn);
void glSetStrokeWidth(GLfloat strokeWidth);
void glSetStrokeAlpha(GLfloat a);
void glSetStrokeColor(GLfloat r, GLfloat g, GLfloat b);
void glSetStrokeColorA(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

GLuint glColorBytesToInt(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
GLuint glColorFloatsToInt(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
GLuint glColorToInt(const GLColor4& color);

void glPushStyle();
void glPopStyle();

void glCheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg);
GLuint glCreateShaderFromText(const std::string& text, GLenum shaderType);

#endif /* GLHELPERS_H_ */
