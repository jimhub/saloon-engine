/*
 * TiledMap.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: james
 */

#include "TiledMap.h"

TiledMap::TiledMap(const char* fileName) {
	// clear out any previously loaded data
	xmlDoc.Clear();

	xmlDoc.LoadFile(fileName);

	if(xmlDoc.Error()) {
		xmlDoc.PrintError();
		return;
	}

	XMLElement* mapElem;

	mapElem = xmlDoc.FirstChildElement("map");

	if(mapElem == NULL) {
		printf("Could not load map element.\n");
		xmlDoc.Clear();
		return;
	}


	tilesX = mapElem->IntAttribute("width");
	tilesY = mapElem->IntAttribute("height");

	tileWidth = mapElem->IntAttribute("tilewidth");
	tileHeight = mapElem->IntAttribute("tileheight");

	mapWidth = tilesX * tileWidth;
	mapHeight = tilesY * tileHeight;

	XMLElement* curTileSet = mapElem->FirstChildElement("tileset");

	while(curTileSet != NULL) {
		TiledMapTileset* ts = new TiledMapTileset(curTileSet);

		tileSets.push_back(ts);

		curTileSet = curTileSet->NextSiblingElement("tileset");
	}

	XMLElement* curLayer = mapElem->FirstChildElement("layer");

	while(curLayer != NULL) {
		layers.push_back(new TiledMapLayer(curLayer));

		curLayer = curLayer->NextSiblingElement("layer");
	}
}

TiledMap::~TiledMap() {
	for (size_t i = 0; i < tileSetTextures.size(); i++) {
		glDeleteTextures( 1, &tileSetTextures[i]);
	}

	for (size_t i = 0; i < tileSets.size(); i++) {
	   delete tileSets[i];
	}

	for (size_t i = 0; i < layers.size(); i++) {
	   delete layers[i];
	}

	xmlDoc.Clear();
}

TiledMapTileset* TiledMap::getTileSet(int i) {
	return tileSets[i];
}

void TiledMap::clear() {
	xmlDoc.Clear();
}

void TiledMap::loadTextures() {

	for (size_t i = 0; i < tileSets.size(); i++) {
		tileSetTextures.push_back(glLoadTexture(tileSets[i]->getImgFile(), GL_NEAREST));
	}

}

void TiledMap::renderLayer(int x, int y, int layerNum) {
	TiledMapTileset* ts = tileSets[0];
	GLuint tex = tileSetTextures[0];

	TiledMapLayer* layer = layers[layerNum];

	int count = layer->getTileCount();

	glPushMatrix();

	glTranslatef(x, -y, 0);

	for(int i = 0; i < count; i++) {
		TiledMapTile* tile = layer->getTile(i);
		glPushMatrix();

		glDrawTexture(tex, tile->getX()*tileWidth, tile->getY()*tileHeight,
				tileWidth, tileHeight, ts->getClip(tile->getGID()));

		glPopMatrix();
	}

	glPopMatrix();
}

int TiledMap::getTilesX() const {
	return tilesX;
}

int TiledMap::getTilesY() const {
	return tilesY;
}

int TiledMap::getMapHeight() const {
	return mapHeight;
}

int TiledMap::getMapWidth() const {
	return mapWidth;
}

int TiledMap::getTileHeight() const {
	return tileHeight;
}

int TiledMap::getTileWidth() const {
	return tileWidth;
}
