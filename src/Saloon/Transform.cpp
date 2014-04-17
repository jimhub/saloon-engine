/*
 * Transform.cpp
 *
 *  Created on: Apr 17, 2014
 *      Author: james
 */

#include "Transform.h"

Transform::Transform(const glm::vec3& pos, const glm::vec3& rot,
		const glm::vec3& scale) {

	this->pos = pos;
	this->rotation = rot;
	this->scale = scale;
}

Transform::~Transform() {
	// TODO Auto-generated destructor stub
}

glm::mat4 Transform::getModel() const {
	glm::mat4 posMatrix = glm::translate(pos);
	glm::mat4 rotXMatrix = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
	glm::mat4 rotYMatrix = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
	glm::mat4 rotZMatrix = glm::rotate(rotation.z, glm::vec3(0, 0, 1));
	glm::mat4 scaleMatrix = glm::scale(scale);

	glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

	return posMatrix * rotMatrix * scaleMatrix;
}
