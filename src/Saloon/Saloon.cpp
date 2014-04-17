/*
 * Saloon.cpp
 *
 *  Created on: Apr 14, 2014
 *      Author: james
 */

#include "Saloon.h"

Saloon::Saloon() :
	_camX(0), _camY(0),
	_camAng(0), _camZoom(1),
	_debugEnabled(true),
	_debugColor(1, 1, 1, 1),
	_displayWidth(0),
	_displayHeight(0),
	_halfDisplayWidth(0),
	_halfDisplayHeight(0),
	_window(nullptr)
{

}

Saloon::~Saloon() {

}

GLfloat Saloon::deltaTime = 1.0f;

int Saloon::init(const char* title, int width, int height, bool windowed, int x, int y) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Slight optimization to prepare the PNG loader prior to loading any images
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		logSDLError(std::cout, "IMG_Init");
		return 1;
	}

	if (TTF_Init() != 0){
		logSDLError(std::cout, "TTF_Init");
		return 1;
	}

	if(windowed) {
		_window = SDL_CreateWindow(title, x, y, width, height,
				SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	}
	else {
		_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				width, height,
				SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
	}

	if (_window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		return 2;
	}

	_displayWidth = width;
	_displayHeight = height;

	_halfDisplayWidth = width/2.0f;
	_halfDisplayHeight = height/2.0f;

	return 0;
}

void Saloon::setDebugColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	_debugColor.r = r;
	_debugColor.g = g;
	_debugColor.b = b;
	_debugColor.a = a;
}

void Saloon::setVSyncEnabled(bool enabled) {
	SDL_GL_SetSwapInterval(enabled);
}

void Saloon::moveCamera(GLfloat x, GLfloat y) {
	_camX += x;
	_camY += y;
}

void Saloon::setCameraPosition(GLfloat x, GLfloat y) {
	_camX = x;
	_camY = y;
}

int Saloon::start() {
	if(_window != nullptr) {

		// Create an OpenGL context associated with the window.
		SDL_GLContext glContext = SDL_GL_CreateContext(_window);

		// Init and check for GL Errors.
		glInit(_displayWidth, _displayHeight);

		GLenum error = glGetError();
		if( error != GL_NO_ERROR )
		{
			logSDLError(std::cout, "GL INIT");
			return 1;
		}

		LTimer fpsTimer;
		fpsTimer.start();
		Uint32 frames = 0, FPS = 0;

		//Our event structure
		SDL_Event e;
		bool quit = false;

		int curTime, prevTime = SDL_GetTicks();

		BMFont debugFont("Fonts/system16.fnt");

		onCreate();


		while (!quit){

			while (SDL_PollEvent(&e)){
				if (e.type == SDL_QUIT)
					quit = true;
				//Use number input to select which clip should be drawn
				if (e.type == SDL_KEYDOWN){
					switch (e.key.keysym.sym){
						case SDLK_ESCAPE:
							quit = true;
							break;
						case SDLK_TAB:
							if(_debugEnabled) {
								setVSyncEnabled(false);
							}
							break;
						default:
							break;
					}
				}
				else if(e.type == SDL_KEYUP) {
					switch (e.key.keysym.sym){
						case SDLK_TAB:
							if(_debugEnabled) {
								setVSyncEnabled(true);
							}
							break;
						default:
							break;
					}
				}
			}

			if(_debugEnabled) {
				debugStart();

				curTime = SDL_GetTicks();

				deltaTime = (curTime - prevTime) / 1000.0f;

				prevTime = curTime;

				if(fpsTimer.getTicks() >= 1000) {
					FPS = frames;
					frames = 0;
					fpsTimer.reset();
				}

				frames++;

				debugWatch("FPS", FPS);
			}

			onUpdate();

			glClear(GL_COLOR_BUFFER_BIT);

			//Reset modelview matrix
			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity();

			glPushMatrix();

			glTranslatef(_halfDisplayWidth, _halfDisplayHeight, 0.0f);

			glPushMatrix();
			// Camera transformations
			glScalef(_camZoom, _camZoom, 1.0f);
			glRotatef(_camAng, 0, 0, 1);
			glTranslatef(-_camX, _camY, 0);

			onRender();

			glPopMatrix();

			glPopMatrix();

			glColor4(_debugColor);
			debugDraw(debugFont);

			SDL_GL_SwapWindow(_window);

		}

		onDestroy();

		glDestroy();

		// Once finished with OpenGL functions, the SDL_GLContext can be deleted.
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(_window);

		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		return 0;
	}
	else {
		logSDLError(std::cout, "Saloon::start");
		return 1;
	}

}

void Saloon::setClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	glClearColor(r, g, b, a);
}

void Saloon::setDebugEnabled(bool enabled) {
	_debugEnabled = enabled;
}
