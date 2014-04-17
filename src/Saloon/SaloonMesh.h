/*
 * SaloonMesh.h
 *
 *  Created on: Apr 16, 2014
 *      Author: james
 */

#ifndef SALOONMESH_H_
#define SALOONMESH_H_

#include "glHelpers.h"
#include <glm/glm.hpp>

class Vertex {
private:

protected:

public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord);

	glm::vec3 pos;
	glm::vec2 texCoord;
};

class SaloonMesh {
private:

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,

		NUM_BUFFERS
	};

	GLuint _vertexArrayObject;
	GLuint _vertexArrayBuffers[NUM_BUFFERS];
	uint _drawCount;

public:
	SaloonMesh(Vertex* verts, uint numVerts);
	virtual ~SaloonMesh();

	void draw();
};

#endif /* SALOONMESH_H_ */
