/*
 * glHelpers.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: james
 */

#include "glHelpers.h"
#include <stack>

using namespace std;

stack<GLStyle> styleStack;

GLStyle* curStyle;

int sWidth, sHeight;

void glInit2DViewPort(int width, int height) {
	glEnable( GL_TEXTURE_2D );

	glViewport( 0, 0, width, height );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void glInit(int screenWidth, int screenHeight) {

	glInit2DViewPort(screenWidth, screenHeight);

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	glClear( GL_COLOR_BUFFER_BIT );

	// set up the default stylee;
	styleStack.push(GLStyle());

	curStyle = &styleStack.top();

	sWidth = screenWidth;
	sHeight = screenHeight;

	//glScalef(1, -1, 1);
}

GLuint glLoadTexture(const char* fileName, GLuint filterMode) {
	GLuint t1 = 0, t2 = 0;
	return glLoadTexture(fileName, t1, t2, filterMode);
}

GLuint glLoadTexture(const char* fileName, GLuint& width, GLuint& height, GLuint filterMode) {
	GLuint texture;			// This is a handle to our texture object
	SDL_Surface *surface;	// This surface will tell us the details of the image
	GLenum texture_format;
	GLint  nOfColors;

	if ( (surface = IMG_Load(fileName)) ) {

		// Check that the image's width is a power of 2
		if ( (surface->w & (surface->w - 1)) != 0 ) {
			printf("warning: '%s' width is not a power of 2\n", fileName);
		}

		// Also check if the height is a power of 2
		if ( (surface->h & (surface->h - 1)) != 0 ) {
			printf("warning: '%s' height is not a power of 2\n", fileName);
		}

	        // get the number of channels in the SDL surface
	        nOfColors = surface->format->BytesPerPixel;
	        if (nOfColors == 4)     // contains an alpha channel
	        {
	                if (surface->format->Rmask == 0x000000ff)
	                        texture_format = GL_RGBA;
	                else
	                        texture_format = GL_BGRA;
	        } else if (nOfColors == 3)     // no alpha channel
	        {
	                if (surface->format->Rmask == 0x000000ff)
	                        texture_format = GL_RGB;
	                else
	                        texture_format = GL_BGR;
	        } else {
	                printf("warning: the image is not truecolor..  this will probably break\n");
	                // this error should not go unhandled
	        }

		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &texture );

		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, texture );

		// Set the texture's stretching properties
	        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode );
	        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode );

		// Edit the texture object's image data using the information SDL_Surface gives us
		glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
	                      texture_format, GL_UNSIGNED_BYTE, surface->pixels );

		width = surface->w;
		height = surface->h;
	}
	else {
		printf("SDL could not load %s: %s\n", fileName, SDL_GetError());
		return 0;
	}

	// Free the SDL_Surface only if it was successfully created
	if ( surface ) {
		SDL_FreeSurface( surface );
	}

	return texture;
}

void glDrawTexture(GLuint texture, GLfloat x, GLfloat y, GLfloat w, GLfloat h,
		GLfloat clipX, GLfloat clipY, GLfloat clipX1, GLfloat clipY1) {

	glBindTexture( GL_TEXTURE_2D, texture );

	glBegin( GL_QUADS );

		glTexCoord2f( clipX, clipY );
		glVertex3f( x, y, 0.0f );

		glTexCoord2f( clipX1, clipY );
		glVertex3f( x + w, y, 0.0f );

		glTexCoord2f( clipX1, clipY1 );
		glVertex3f( x + w, y + h, 0.0f );

		glTexCoord2f( clipX, clipY1 );
		glVertex3f( x, y + h, 0.0f );
	glEnd();

}


void glDrawTexture(GLuint texture, const GLRectF &quad, const GLRectF &clip) {

		glDrawTexture(texture, quad.x, quad.y, quad.w, quad.h,
				clip.x, clip.y, clip.x + clip.w, clip.y + clip.h);

}

void glDrawTexture(GLuint texture, float x, float y, float w, float h,
		const GLRectF& clip) {
	glDrawTexture(texture, x, y, w, h,
			clip.x, clip.y, clip.x + clip.w, clip.y + clip.h);
}

void glColor4(const GLColor4& color) {
	glColor4f(color.r, color.g, color.b, color.a);
}

void glDrawLine(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1) {
	glDisable(GL_TEXTURE_2D);

	glPushAttrib(GL_CURRENT_BIT);
	glColor4(curStyle->strokeColor);

	glBegin(GL_QUADS);
		glVertex3f(x0, y0, 0.0f);
		glVertex3f(x0 + curStyle->strokeWidth, y0, 0.0f);
		glVertex3f(x1 + curStyle->strokeWidth, y1, 0.0f);
		glVertex3f(x1, y1, 0.0f);
	glEnd();

	glPopAttrib();
	glEnable(GL_TEXTURE_2D);
}

void glDrawRect(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1) {
	glDisable(GL_TEXTURE_2D);

	glPushAttrib(GL_CURRENT_BIT);
	glColor4(curStyle->fillColor);

	glBegin(GL_QUADS);
		glVertex3f(x0, y0, 0.0f);
		glVertex3f(x1, y0, 0.0f);
		glVertex3f(x1, y1, 0.0f);
		glVertex3f(x0, y1, 0.0f);
	glEnd();

	glPopAttrib();
	glEnable(GL_TEXTURE_2D);
}

void glDrawRect(const GLRectF& rect) {
	glDrawRect(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h);
}

void glDrawCircle(GLfloat cx, GLfloat cy, GLfloat radius) {
	glDisable(GL_TEXTURE_2D);

	glPushAttrib(GL_CURRENT_BIT);
	glColor4(curStyle->fillColor);

	float seg = TWO_PI/20.0f;

	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(cx, cy, 0.0f);

		for(float a=0; a < TWO_PI + seg; a += seg) {
			glVertex3f(cx + radius*cosf(a), cy + radius*sinf(a), 0.0f);
		}

	glEnd();

	glPopAttrib();
	glEnable(GL_TEXTURE_2D);
}


void glDrawPoly(GLfloat verts[], int numVerts) {
	glDisable(GL_TEXTURE_2D);

	glPushAttrib(GL_CURRENT_BIT);
	glColor4(curStyle->fillColor);

	numVerts *= 2;

	glBegin(GL_POLYGON);

		for(int i=0; i < numVerts; i += 2) {
			glVertex3f(verts[i], verts[i+1], 0.0f);
		}

	glEnd();

	glPopAttrib();
	glEnable(GL_TEXTURE_2D);
}

void glSetFill(bool fillOn) {
	curStyle->fillOn = fillOn;
}

void glSetAlpha(GLfloat a) {
	curStyle->fillColor.a = a;
}

void glSetColor(GLfloat r, GLfloat g, GLfloat b) {
	curStyle->fillColor.r = r;
	curStyle->fillColor.g = g;
	curStyle->fillColor.b = b;
}

void glSetColorA(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	curStyle->fillColor.r = r;
	curStyle->fillColor.g = g;
	curStyle->fillColor.b = b;
	curStyle->fillColor.a = a;
}

void glSetStroke(bool strokeOn) {
	curStyle->strokeOn = strokeOn;
}

void glSetStrokeWidth(GLfloat strokeWidth) {
	curStyle->strokeWidth = strokeWidth;
}

void glSetStrokeAlpha(GLfloat a) {
	curStyle->strokeColor.a = a;
}

void glSetStrokeColor(GLfloat r, GLfloat g, GLfloat b) {
	curStyle->strokeColor.r = r;
	curStyle->strokeColor.g = g;
	curStyle->strokeColor.b = b;
}

void glSetStrokeColorA(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	curStyle->strokeColor.r = r;
	curStyle->strokeColor.g = g;
	curStyle->strokeColor.b = b;
	curStyle->strokeColor.a = a;
}

void glPushStyle() {
	styleStack.push(GLStyle(styleStack.top()));

	curStyle = &styleStack.top();

}

void glDestroy() {
	while(!styleStack.empty()) {
		styleStack.pop();
	}
}


void glPopStyle() {
	if(!styleStack.empty()) {
		styleStack.pop();

		curStyle = &styleStack.top();
	}
}

GLuint glCreateRenderTarget(GLuint* renderedTexture, GLuint width, GLuint height, GLuint filterMode) {

	GLuint fbo;
	glGenFramebuffers(1 , &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// The texture we're going to render to
	glGenTextures(1, renderedTexture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, *renderedTexture);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,GL_RGBA, GL_UNSIGNED_BYTE, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *renderedTexture, 0);

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	glClear( GL_COLOR_BUFFER_BIT );

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return fbo;
}

void glActivateRenderTarget(GLuint FBO, GLuint width, GLuint height) {
	// Render to our framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glInit2DViewPort(width, height);
}

void glDeactivateRenderTarget() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glInit2DViewPort(sWidth, sHeight);
}

GLuint glColorBytesToInt(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
	GLuint color;
	GLubyte* bytes = (GLubyte*)&color;

	bytes[0] = r;
	bytes[1] = g;
	bytes[2] = b;
	bytes[3] = a;

	return color;
}

GLuint glColorFloatsToInt(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	GLuint color;
	GLubyte* bytes = (GLubyte*)&color;

	bytes[0] = (GLubyte)(r*255);
	bytes[1] = (GLubyte)(g*255);
	bytes[2] = (GLubyte)(b*255);
	bytes[3] = (GLubyte)(a*255);

	return color;
}

GLuint glColorToInt(const GLColor4& color) {
	return glColorFloatsToInt(color.r, color.g, color.b, color.a);
}
