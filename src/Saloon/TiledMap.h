/*
 * TiledMap.h
 *
 *  Created on: Feb 23, 2014
 *      Author: james
 */

#ifndef TILEDMAP_H_
#define TILEDMAP_H_

#include <vector>

#include "glHelpers.h"

#include "TiledMapTileset.h"
#include "TiledMapLayer.h"

#include "tinyxml2.h"

using namespace tinyxml2;

class TiledMap {
private:
	XMLDocument xmlDoc;

	int mapWidth, mapHeight;
	int tileWidth, tileHeight;
	int tilesX, tilesY;

	std::vector<TiledMapTileset*> tileSets;
	std::vector<TiledMapLayer*> layers;

	std::vector<GLuint> tileSetTextures;

public:
	TiledMap(const char* fileName);
	virtual ~TiledMap();

	void clear();

	TiledMapTileset* getTileSet(int i);
	void loadTextures();

	void renderLayer(int x, int y, int layerNum);
	int getTilesX() const;
	int getTilesY() const;
	int getMapHeight() const;
	int getMapWidth() const;
	int getTileHeight() const;
	int getTileWidth() const;
};

#endif /* TILEDMAP_H_ */
