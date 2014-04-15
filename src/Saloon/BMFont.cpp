/*
 * BMFont.cpp
 *
 *  Created on: Feb 26, 2014
 *      Author: james
 */

#include "BMFont.h"
#include "tinyxml2.h"

using namespace tinyxml2;

BMFont::BMFont(const char* fileName) : tabSize(4) {
	XMLDocument xml;
	xml.LoadFile(fileName);

	if(xml.Error()) {
		xml.PrintError();
		return;
	}

	XMLElement* font;

	font = xml.FirstChildElement("font");

	if(font == NULL) {
		printf("Could not load font element.\n");
		xml.Clear();
		return;
	}

	XMLElement* common = font->FirstChildElement("common");

	lineHeight = common->IntAttribute("lineHeight");
	texWidth = common->IntAttribute("scaleW");
	texHeight = common->IntAttribute("scaleH");

	XMLElement* page = font->FirstChildElement("pages")->FirstChildElement("page");

	texture = glLoadTexture(page->Attribute("file"), GL_LINEAR);

	XMLElement* curChar = font->FirstChildElement("chars")->FirstChildElement("char");

	while(curChar != NULL) {

		GLfloat clipX = curChar->FloatAttribute("x") / texWidth;
		GLfloat clipY = curChar->FloatAttribute("y") / texHeight;

		GLfloat w = curChar->FloatAttribute("width");
		GLfloat h = curChar->FloatAttribute("height");

		GLfloat clipW = w / texWidth;
		GLfloat clipH = h / texHeight;

		this->chars.insert(std::pair<int, BMFontChar>(curChar->IntAttribute("id"),
				BMFontChar(w, h, clipX, clipY, clipW, clipH,
								curChar->IntAttribute("xoffset"),
								curChar->IntAttribute("yoffset"),
								curChar->IntAttribute("xadvance"))));

		curChar = curChar->NextSiblingElement("char");
	}

	xml.Clear();
}

BMFont::~BMFont() {
	glDeleteTextures(1, &texture);
}

void BMFont::setTabSize(int tabSize) {
	this->tabSize = tabSize;
}

void BMFont::renderText(GLfloat x, GLfloat y, const char* text) const {

	GLfloat origX = x;

	while(*text != '\0') {

		if(*text == '\n') {
			x = origX;
			y += lineHeight;
		}
		else if(*text == '\t') {
			x += chars.at(' ').getAdvanceX()*tabSize;
		}
		else {
			int curChar = *text;

			// char unsupported??
			if(chars.find(curChar) == chars.end())
				curChar = 191; //

			const BMFontChar c = chars.at(curChar);

			glDrawTexture(texture, x+c.getOffsetX(), y+c.getOffsetY(), c.getW(), c.getH(), c.getClip());

			x += c.getAdvanceX();
		}

		text++;

	}
}
