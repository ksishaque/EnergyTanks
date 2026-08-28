/*!
\file Transform.cpp
\author Khaled S. Ishaque
        Kevin Shin
\date 9-15-2022
\brief
    function definitions for object transform components
\par Copyright © 2022 DigiPen, All rights reserved.
*/

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Transform.h"
#include "Component.h"
#include "Trace.h"

Transform::Transform(const glm::vec3 &trans, const glm::vec3 &scale, float rot) : Component(ComponentTypeEnum::cTransform), dirtyMatrix(true), translation(trans), rotation(rot), scale(scale), transformMatrix() {
#ifdef DEBUG_SYSTEM
    Trace::message("Transform Vec3 Version Made.");
#endif
}


Transform::Transform(float x, float y, float z, float xS, float yS, float zS, float rot) : Component(ComponentTypeEnum::cTransform), dirtyMatrix(true), translation(x, y, z), rotation(rot), scale(xS, yS, zS), transformMatrix() {
#ifdef DEBUG_SYSTEM
    Trace::message("Transform Float Version Made.");
#endif
}

Transform::~Transform() {
#ifdef DEBUG_SYSTEM
    Trace::message("Destroying Transform Component");
#endif
}

Transform::Transform(const Transform& baseTransform) : Component(ComponentTypeEnum::cTransform) {
    dirtyMatrix = baseTransform.dirtyMatrix;
    rotation = baseTransform.rotation;
    translation = baseTransform.translation;
    scale = baseTransform.scale;
    transformMatrix = baseTransform.transformMatrix;
#ifdef DEBUG_SYSTEM
    Trace::message("Transform Copy Ctor Finished");
#endif
}

void Transform::setRotatePos(float newRotate) {
	if (newRotate == rotation) {
		return;
	}
    dirtyMatrix = true;
    rotation = newRotate;
    //Setting the new position when rotating
    while (rotation < 0) {
        rotation += 360;
    }
    while (rotation >= 360) {
        rotation -= 360;
    }
}

float Transform::getRotation() const {
    return rotation;
}

void Transform::setTranslation(const glm::vec3 &newTrans) {
	if (newTrans == translation) {
		return;
	}
	dirtyMatrix = true;
    translation = newTrans;
    //Trace::message("New Translation: X: %f, Y: %f, Z: %f.", translation.x, translation.y, translation.z);
}

void Transform::setScale(float newScale) {
	if (newScale == scale.x || newScale == scale.y) {
		return;
	}
	dirtyMatrix = true;
    scale.x = newScale;
    scale.y = newScale;
    scale.z = 1;
    //Trace::message("New Scale: X: %f, Y: %f, Z: %f.", scale.x, scale.y, scale.z);
}

glm::vec3 Transform::getTranslation() const {
    return translation;
}

glm::vec3 Transform::getScale() const {
    return scale;
}

const glm::mat4& Transform::getMatrix() const {

	//	Ensure the matrix is up to date
	updateMatrix();

	//	Return
    return transformMatrix;
}

void Transform::updateMatrix() const {

	//	If the matrix is out of date, then update it
	if(dirtyMatrix) {

		//	Update `transformMatrix`
        transformMatrix = glm::translate(translation) * glm::rotate(glm::radians(rotation), glm::vec3(0, 0, 1)) * glm::scale(scale);

		//	Release the `dirtyMatrix` flag
		dirtyMatrix = false;
	}

}

Component* Transform::clone() const {
    Transform* transformClone = new Transform();
    if (transformClone != nullptr) {
        transformClone->dirtyMatrix = dirtyMatrix;
        transformClone->transformMatrix = transformMatrix;
        transformClone->scale = scale;
        transformClone->rotation = rotation;
        transformClone->translation = translation;
#ifdef DEBUG_SYSTEM
        Trace::message("Transform Clone Was Successful.");
#endif
        return transformClone;
    }
    else {
#ifdef DEBUG_SYSTEM
        Trace::message("Transform Clone Has Failed.");
#endif
        return nullptr;
    }
}

void Transform::setTranslation(float x, float y, float z) {
	if (translation.x == x && translation.y == y && translation.z == z) {
		return;
	}
	dirtyMatrix = true;
    translation.x = x;
	translation.y = y;
	translation.z = z;
    //Trace::message("New Translation: X: %f, Y: %f, Z: %f.", translation.x, translation.y, translation.z);
}

void Transform::setScale(float x, float y, float z) {
	if (scale.x == x && scale.y == y && scale.z == z) {
		return;
	}
	dirtyMatrix = true;
    scale.x = x;
	scale.y = y;
	scale.z = z;
    //Trace::message("New Scale: X: %f, Y: %f, Z: %f.", scale.x, scale.y, scale.z);
}

void Transform::setScale(const glm::vec3 &scale) {
	if (this -> scale == scale) {
		return;
	}
	dirtyMatrix = true;
    this -> scale = scale;
}