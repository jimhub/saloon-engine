/*
 * Debug.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: james
 */

#include "Debug.h"

std::stringstream debugStr;

size_t logIndex = 0;

SDL_Texture* debugText;

void debugStart() {
	debugStr.str("");
}

void debugWatch(const char* name, Uint32 val) {
	debugStr << name << ": " << val << std::endl;
}

void debugWatch(const char* name, const std::string& val) {
	debugStr << name << ": " << val << std::endl;
}

void debugWatch(const char* name, double val) {
	debugStr << name << ": " << val << std::endl;
}

void debugLog(const char* text) {
	debugStr << text << std::endl;
}

void debugDraw(const BMFont& font, GLfloat x, GLfloat y) {
	font.renderText(x, y, debugStr.str().c_str());
}

