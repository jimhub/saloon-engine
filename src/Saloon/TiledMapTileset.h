/*
 * TiledMapTileset.h
 *
 *  Created on: Feb 23, 2014
 *      Author: james
 */

#ifndef TILEDMAPTILESET_H_
#define TILEDMAPTILESET_H_

#include <vector>
#include "glHelpers.h"

#include "tinyxml2.h"
using namespace tinyxml2;

class TiledMapTileset {
private:
	int tileWidth, tileHeight;
	int firstGID;

	const char* name;
	const char* imgFile;

	std::vector<GLRectF> clips;

public:
	TiledMapTileset(XMLElement* tileSetElem);
	TiledMapTileset(const char* name, const char* imgFile, int tileW, int tileH, int firstGID);

	virtual ~TiledMapTileset();
	const char* getImgFile() const;
	const char* getName() const;
	int getTileHeight() const;
	int getTileWidth() const;

	const GLRectF& getClip(int gid);

};

#endif /* TILEDMAPTILESET_H_ */
