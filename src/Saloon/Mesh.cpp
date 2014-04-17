/*
 * Mesh.cpp
 *
 *  Created on: Apr 16, 2014
 *      Author: james
 */

#include "Mesh.h"
#include <vector>

Vertex::Vertex(const glm::vec3& pos, const glm::vec2& texCoord) {
	this->pos = pos;
	this->texCoord = texCoord;
}


Mesh::Mesh() {
	_drawCount = 0;
	_vertexArrayObject = 0;
}


Mesh::~Mesh() {
	free();
}

void Mesh::free() {
	if(_vertexArrayObject != 0) {
		glDeleteVertexArrays(1, &_vertexArrayObject);
		_vertexArrayObject = 0;
		_drawCount = 0;
	}
}

void Mesh::draw() {
	glBindVertexArray(_vertexArrayObject);

	glDrawArrays(GL_TRIANGLES, 0, _drawCount);

	glBindVertexArray(0);
}


void Mesh::createFromVertices(Vertex* verts, uint numVerts) {
	_drawCount = numVerts;

	glGenVertexArrays(1, &_vertexArrayObject);
	glBindVertexArray(_vertexArrayObject);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;

	positions.reserve(numVerts);
	texCoords.reserve(numVerts);

	for(uint i = 0; i < numVerts; i++) {
		positions.push_back(verts[i].pos);
		texCoords.push_back(verts[i].texCoord);
	}

	glGenBuffers(NUM_BUFFERS, _vertexArrayBuffers);

	// Set up position buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVerts*sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Set up texCoord buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVerts*sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);


	glBindVertexArray(0);
}
