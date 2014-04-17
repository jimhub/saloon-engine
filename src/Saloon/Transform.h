/*
 * Transform.h
 *
 *  Created on: Apr 17, 2014
 *      Author: james
 */

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform {
private:
	glm::vec3 pos;
	glm::vec3 rotation;
	glm::vec3 scale;

public:
	Transform(const glm::vec3& pos = glm::vec3(0, 0, 0),
			const glm::vec3& rot = glm::vec3(0, 0, 0),
			const glm::vec3& scale = glm::vec3(1, 1, 1));

	virtual ~Transform();

	glm::mat4 getModel() const;

	glm::vec3& getPos() {
		return pos;
	}

	void setPos(const glm::vec3& pos) {
		this->pos = pos;
	}

	glm::vec3& getRotation() {
		return rotation;
	}

	void setRotation(const glm::vec3& rotation) {
		this->rotation = rotation;
	}

	glm::vec3& getScale() {
		return scale;
	}

	void setScale(const glm::vec3& scale) {
		this->scale = scale;
	}
};

#endif /* TRANSFORM_H_ */
