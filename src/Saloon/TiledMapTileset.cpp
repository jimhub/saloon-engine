/*
 * TiledMapTileset.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: james
 */

#include "TiledMapTileset.h"

TiledMapTileset::TiledMapTileset(XMLElement* tileSetElem) {
	name = tileSetElem->Attribute("name");
	tileWidth = tileSetElem->IntAttribute("tilewidth");
	tileHeight = tileSetElem->IntAttribute("tileheight");

	firstGID = tileSetElem->IntAttribute("firstgid");

	XMLElement* imgElem = tileSetElem->FirstChildElement("image");

	if(imgElem == NULL) {
		printf("Could not load image element.\n");
		return;
	}

	imgFile = imgElem->Attribute("source");

	int imgW = imgElem->IntAttribute("width");
	int imgH = imgElem->IntAttribute("height");

	int numCols = imgW / tileWidth;
	int numRows = imgH / tileHeight;

	GLfloat clipWidth = ((GLfloat)tileWidth)/imgW;
	GLfloat clipHeight = ((GLfloat)tileHeight)/imgH;

	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < numCols; j++) {
			GLRectF clip;

			clip.x = j*clipWidth;
			clip.y = i*clipHeight;
			clip.w = clipWidth;
			clip.h = clipHeight;

			clips.push_back(clip);
		}
	}
}

TiledMapTileset::TiledMapTileset(const char* name, const char* imgFile,
		int tileW, int tileH, int firstGID) {
	this->name = name;
	this->imgFile = imgFile;
	tileWidth = tileW;
	tileHeight = tileH;
	this->firstGID = firstGID;
}

const char* TiledMapTileset::getImgFile() const {
	return imgFile;
}

const char* TiledMapTileset::getName() const {
	return name;
}

int TiledMapTileset::getTileHeight() const {
	return tileHeight;
}

int TiledMapTileset::getTileWidth() const {
	return tileWidth;
}

TiledMapTileset::~TiledMapTileset() {
	clips.clear();
}

const GLRectF& TiledMapTileset::getClip(int gid) {
	return clips[gid - firstGID];
}
