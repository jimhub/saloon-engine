/*
 * TiledMapTile.h
 *
 *  Created on: Feb 23, 2014
 *      Author: james
 */

#ifndef TILEDMAPTILE_H_
#define TILEDMAPTILE_H_

class TiledMapTile {
private:
	int x;
	int y;
	int gid;

public:
	TiledMapTile(int x, int y, int gid);
	virtual ~TiledMapTile();
	int getGID() const;
	int getX() const;
	int getY() const;
};

#endif /* TILEDMAPTILE_H_ */
