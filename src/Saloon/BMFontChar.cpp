/*
 * BMFontChar.cpp
 *
 *  Created on: Feb 26, 2014
 *      Author: james
 */

#include "BMFontChar.h"

BMFontChar::BMFontChar(GLfloat w, GLfloat h, GLfloat x, GLfloat y, GLfloat x1, GLfloat y1, int offsetX, int offsetY, int advanceX) :
	w(w), h(h), clip(x, y, x1, y1), offsetX(offsetX), offsetY(offsetY), advanceX(advanceX)
{
	// TODO Auto-generated constructor stub

}

BMFontChar::~BMFontChar() {
	// TODO Auto-generated destructor stub
}

int BMFontChar::getAdvanceX() const {
	return advanceX;
}

const GLRectF& BMFontChar::getClip() const {
	return clip;
}

int BMFontChar::getOffsetX() const {
	return offsetX;
}

int BMFontChar::getOffsetY() const {
	return offsetY;
}
