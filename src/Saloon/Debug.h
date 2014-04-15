/*
 * Debug.h
 *
 *  Created on: Feb 23, 2014
 *      Author: james
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include "BMFont.h"
#include <sstream>

void debugStart();
void debugWatch(const char* name, Uint32 val);
void debugWatch(const char* name, std::string val);
void debugWatch(const char* name, double val);
void debugLog(const char*);
void debugDraw(const BMFont& font, GLfloat x = 5, GLfloat y = 5);

#endif /* DEBUG_H_ */
