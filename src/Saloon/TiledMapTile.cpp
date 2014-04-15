/*
 * TiledMapTile.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: james
 */

#include "TiledMapTile.h"

TiledMapTile::TiledMapTile(int x, int y, int gid) : x(x), y(y), gid(gid) {
}

int TiledMapTile::getGID() const {
	return gid;
}

int TiledMapTile::getX() const {
	return x;
}

int TiledMapTile::getY() const {
	return y;
}

TiledMapTile::~TiledMapTile() {
	// TODO Auto-generated destructor stub
}

