/*!
\file Physics.cpp
\author Khaled S. Ishaque
\date 9-9-2022
\brief
    function definitions for object physics components
\par Copyright © 2022 DigiPen, All rights reserved.
*/

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Component.h"
#include "Force.h"
#include "GameObject.h"
#include "Trace.h"
#include "Transform.h"
#include "Physics.h"

/*!
\fn     Physics::Physics() : Component(ComponentTypeEnum::cPhysics)
\return Nothing
\brief
        See Physics.h
*/
Physics::Physics(float translX, float translY, float translZ,
    float accelX, float accelY, float accelZ,
    float velX, float velY, float velZ) : Component(ComponentTypeEnum::cPhysics), forces() {
    prevTranslation = glm::vec3(translX, translY, translZ);
    acceleration = glm::vec3(accelX, accelY, accelZ);
    velocity = glm::vec3(velX, velY, velZ);
    velocityRotate = 0;
#ifdef DEBUG_SYSTEM
    Trace::message("Physics Component Made.");
#endif
}

/*!
\fn     Physics::Physics(const Physics& basePhysics) : Component(ComponentTypeEnum::cPhysics)
\param  basePhysics
            Physics class to copy
\return Nothing
\brief
        See Physics.h
*/
Physics::Physics(const Physics& basePhysics) : Component(ComponentTypeEnum::cPhysics), forces() {
    prevTranslation = basePhysics.prevTranslation;
    acceleration = basePhysics.acceleration;
    velocity = basePhysics.velocity;
    velocityRotate = basePhysics.velocityRotate;
#ifdef DEBUG_SYSTEM
    Trace::message("Physics Copy Ctor Completed");
#endif
}

/*!
\fn     Physics::~Physics()
\return Nothing
\brief  
        See Physics.h
*/
Physics::~Physics() {

}

/*!
\fn     float Physics::getRotateVelocity()
\return velocityRotate
\brief
        See Physics.h
*/
float Physics::getRotateVelocity() {
    return velocityRotate;
}

/*!
\fn     void Physics::accelerationSet()
\param  newAccel
            new acceleration value
\return Nothing
\brief
        See Physics.h
*/
void Physics::setAcceleration(glm::vec3 newAccel) {
    acceleration = newAccel;
}

/*!
\fn     void Physics::setVelocity()
\param  newVel
            new velocity value
\return Nothing
\brief
        See Physics.h
*/
void Physics::setVelocity(glm::vec3 newVel) {
    velocity = newVel;
}

/*!
\fn     glm::vec3 Physics::getAcceleration()
\return acceleration
\brief
        See Physics.h
*/
glm::vec3 Physics::getAcceleration() {
    return acceleration;
}

/*!
\fn     glm::vec3 Physics::getOldTransl()
\return prevTranslation
\brief
        See Physics.h
*/
glm::vec3 Physics::getOldTransl() {
    return prevTranslation;
}

/*!
\fn     glm::vec3 Physics::getVelocity()
\return velocity
\brief
        See Physics.h
*/
glm::vec3 Physics::getVelocity() {
    return velocity;
}

/*!
\fn     void Physics::update(float dt)
\param  dt
           change in time
\return Nothing
\brief
        See Physics.h
*/
void Physics::update(float dt) {
    GameObjectPtr object = Component::getParent();
    if (object->has(ComponentTypeEnum::cTransform)) {
		updateOldTrans();

        velocity += acceleration * dt;

        glm::vec3 translTemp = prevTranslation;
		float velFX = 1;

		for(std::vector<Force*>::iterator iter = forces.begin(); iter != forces.end();) {
			if((**iter).apply(translTemp, velFX, dt)) {
				iter = forces.erase(iter);
			}
			else {
				++iter;
			}
		}

        translTemp += velocity * dt * velFX;

		TransformPtr currTransform = (TransformPtr)object->get(ComponentTypeEnum::cTransform);
        currTransform->setTranslation(translTemp);
		currTransform->setRotatePos(currTransform->getRotation() + (velocityRotate * dt));
    }
}

Component* Physics::clone() const {
    Physics* newPhysics = new Physics(0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (newPhysics != NULL) {
        newPhysics->acceleration = acceleration;
        newPhysics->prevTranslation = prevTranslation;
        newPhysics->velocity = velocity;
        newPhysics->velocityRotate = velocityRotate;
        return newPhysics;
    }
    else {
        return NULL;
    }
}

/*!
\fn     void Physics::setVelocity()
\param  rv
            new retoation velocity
\return Nothing
\brief
        See Physics.h
*/
void Physics::setVelocityRotate(float rv) {
    velocityRotate = rv;
}

/*!
\fn     void Physics::setVelocity()
\param  newVel
            new velocity value
\return Nothing
\brief
        See Physics.h
*/
void Physics::setRotatedVelocity(glm::vec3 newVel) {

	//	Variable: parent object
	GameObject *parent = getParent();

	//	Check `parent`
	if(parent == nullptr) return;

	//	Variable: tranformation of `parent`
	Transform *trans = dynamic_cast<Transform *>(parent -> get(ComponentTypeEnum::cTransform));

	//	Check `trans`
	if(trans == nullptr) return;

	//	Set `velocity` to rotated `newVel`
    velocity = glm::rotate(newVel, glm::radians(trans -> getRotation()), glm::vec3(0, 0, 1));
}

/*!
\fn     void Physics::updateOldTrans()
\brief  See Physics.h
*/
void Physics::updateOldTrans() {

	//	Variable: parent object
	GameObject *parent = getParent();

	//	Check `parent`
	if(parent == nullptr) {
#ifdef DEBUG_SYSTEM
		Trace::error("No parent for physics");
#endif
		return;
	}

	//	Variable: transformation to match
	Transform *trans = dynamic_cast<Transform *>(parent -> get(ComponentTypeEnum::cTransform));

	//	Check `trans`
	if(trans == nullptr) {
#ifdef DEBUG_SYSTEM
		Trace::error("Parent has no transformation (physics)");
#endif
		return;
	}

	//	Update `prevTranslation`
	prevTranslation = trans -> getTranslation();
}

/*!
\fn     void Physics::setOldTrans(const glm::vec3 &pTrans)
\param  rv
            new previous translation
\return Nothing
\brief
        See Physics.h
*/
void Physics::setOldTrans(const glm::vec3 &pTrans) {
   prevTranslation = pTrans;
}

/*!
\fn     void Physics::addForce(const glm::vec3 &dir, float mag, float time)
\param  dir
            direction vector
\param  mag
            magnitude
\param  time
            lifetime
\return Nothing
\brief
        See Physics.h
*/
void Physics::addForce(const glm::vec3 &dir, float mag, float time) {
   forces.push_back(new Force(dir, mag, time));
}

/*!
\fn     void Physics::clearForces()
\brief
        See Physics.h
*/
void Physics::clearForces() {
   for(Force* force : forces) {
	   delete force;
   }
   forces.clear();
}