/*
 * TiledMapLayer.h
 *
 *  Created on: Feb 23, 2014
 *      Author: james
 */

#ifndef TILEDMAPLAYER_H_
#define TILEDMAPLAYER_H_

#include <vector>

#include "TiledMapTile.h"

#include "tinyxml2.h"
using namespace tinyxml2;

class TiledMapLayer {
private:
	int _curTile;

	int width, height;
	const char* name;

	std::vector<TiledMapTile*> tiles;

public:
	TiledMapLayer(XMLElement* layerElem);
	TiledMapLayer(const char* name, int width, int height);

	virtual ~TiledMapLayer();
	int getHeight() const;
	const char* getName() const;
	int getWidth() const;

	void addTile(int tileNum);

	int getTileCount() const;
	TiledMapTile* getTile(int i) const;
};

#endif /* TILEDMAPLAYER_H_ */
