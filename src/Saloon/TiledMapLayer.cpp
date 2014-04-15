/*
 * TiledMapLayer.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: james
 */

#include "TiledMapLayer.h"

TiledMapLayer::TiledMapLayer(XMLElement* layerElem) {
	name = layerElem->Attribute("name");
	width = layerElem->IntAttribute("width");
	height = layerElem->IntAttribute("height");

	XMLElement* data = layerElem->FirstChildElement("data");

	if(data == NULL) {
		printf("Could not load layer data element.\n");
		return;
	}

	_curTile = 0;

	XMLElement* curTile = data->FirstChildElement("tile");

	while(curTile != NULL) {

		addTile(curTile->IntAttribute("gid"));

		curTile = curTile->NextSiblingElement("tile");
	}
}

TiledMapLayer::TiledMapLayer(const char* name, int width, int height) : name(name), width(width), height(height) {
	_curTile = 0;
}

int TiledMapLayer::getHeight() const {
	return height;
}

const char* TiledMapLayer::getName() const {
	return name;
}

int TiledMapLayer::getWidth() const {
	return width;
}

TiledMapLayer::~TiledMapLayer() {
	for (size_t i = 0; i < tiles.size(); i++) {
	   delete tiles[i];
	}
}


void TiledMapLayer::addTile(int tileNum) {
	// Do not add tile if tileNum == 0
	int x, y;

	if(tileNum > 0) {
		// Calculate the x and y position of the tile based on current tile count
		// and the layer's dimensions.

		x = _curTile % width;
		y = _curTile / width;

		tiles.push_back(new TiledMapTile(x, y, tileNum));
	}

	_curTile++;
}

TiledMapTile* TiledMapLayer::getTile(int i) const {
	return tiles[i];
}

int TiledMapLayer::getTileCount() const {
	return tiles.size();
}
