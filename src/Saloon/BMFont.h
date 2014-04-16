/*
 * BMFont.h
 *
 *  Created on: Feb 26, 2014
 *      Author: james
 */

#ifndef BMFONT_H_
#define BMFONT_H_

#include <map>
#include "BMFontChar.h"

class BMFont {
private:
	std::map<int, BMFontChar> chars;

	int lineHeight;
	GLuint texWidth, texHeight;
	int tabSize;

	GLuint texture;

public:
	BMFont(const char* fileName);
	virtual ~BMFont();

	void renderText(GLfloat x, GLfloat y, const char* text) const;
	void setTabSize(int tabSize);
};

#endif /* BMFONT_H_ */
