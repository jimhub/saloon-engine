/*
 * BMFontChar.h
 *
 *  Created on: Feb 26, 2014
 *      Author: james
 */

#ifndef BMFONTCHAR_H_
#define BMFONTCHAR_H_

#include "glHelpers.h"

class BMFontChar {
private:
	GLRectF clip;

	int offsetX;
	int offsetY;

	int advanceX;

	GLfloat w, h;

public:
	BMFontChar(GLfloat w, GLfloat h, GLfloat x, GLfloat y, GLfloat x1, GLfloat y1, int offsetX, int offsetY, int advanceX);
	virtual ~BMFontChar();
	int getAdvanceX() const;
	const GLRectF& getClip() const;
	int getOffsetX() const;
	int getOffsetY() const;

	GLfloat getH() const {
		return h;
	}

	GLfloat getW() const {
		return w;
	}
};

#endif /* BMFONTCHAR_H_ */
