/*
 * Saloon.h
 *
 *  Created on: Apr 14, 2014
 *      Author: james
 */

#ifndef SALOON_H_
#define SALOON_H_

#include "SDLHelpers.h"
#include "glHelpers.h"
#include "BMFont.h"
#include "Debug.h"
#include "LTimer.h"

#include "SaloonHelpers.h"
#include "SaloonTexture.h"

class Saloon {
private:
	GLfloat _camX, _camY;
	GLfloat _camAng, _camZoom;

	bool _debugEnabled;
	GLColor4 _debugColor;

	int _displayWidth, _displayHeight;
	GLfloat _halfDisplayWidth, _halfDisplayHeight;

	SDL_Window* _window;

protected:


public:
	Saloon();
	virtual ~Saloon();

	static GLfloat deltaTime;

	int init(const char* title, int width, int height, bool windowed=false, int x=0, int y=0);

	void moveCamera(GLfloat x, GLfloat y);
	void setCameraPosition(GLfloat x, GLfloat y);
	void setClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a=1.0f);
	void setDebugColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a=1.0f);
	void setDebugEnabled(bool enabled=true);

	void setVSyncEnabled(bool enabled=true);

	int start();

	virtual void onCreate() {};
	virtual void onUpdate() {};
	virtual void onRender() {};
	virtual void onDestroy() {};
};

#endif /* SALOON_H_ */
