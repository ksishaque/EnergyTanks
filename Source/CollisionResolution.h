/*****************************************************************//**
 * \file   CollisionResolution.h
 * \brief  
 * 
 * \author Luke Tseng
 * \date   October 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
#pragma once
#include "glm/glm.hpp"

#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"
#include "LineCollider.h"
#include "Collider.h"
#include "Behavior.h"
#include "PowerUp.h"
#include "BehaviorPlayer.h"
#include "BehaviorPowerUp.h"

#define TANKBOUNCE

struct BounceInfo{
	bool happen = false;
	float distance;
	glm::vec3 contact;
	glm::vec3 normal;
};

typedef void (*collisionResolver) (GameObject*, glm::vec3&);
/**
 * death Sets to destroy gameobject
 * 
 * \param gameobject Gameobject to destroy
 * \param v Does nothing
 */
void death(GameObject* gameobject, glm::vec3& v);
/**
 * caseBulletWall When bullet and tank collide
 *
 * \param tank Destroys tank
 * \param bullet Destroys bullet
 */
void caseDestroyBoth(GameObject* tank, GameObject* bullet);
/**
 * caseBulletWall When bullet and wall collide
 * 
 * \param object Reflects object
 * \param info Info of reflect
 * \return True if the object was moved
 */
bool caseBounce(GameObject* object, const BounceInfo& info);
/**
 * caseBulletWall When bullet and wall collide
 * 
 * \param object Pushes object
 * \param info Info of opponent's reflect
 */
void caseKnockback(GameObject* object, const BounceInfo& info);


bool slideOnLine(GameObject* obj, const BounceInfo& info);
/**
 * collisionCases Tests cases of both colliders and determines which resolution to use
 *
 * \param col1 First collider
 * \param mov1 If first object moved
 * \param dis1 Displacement calculated for second collider, if applicable
 * \param col2 Second collider
 * \param mov2 If second object moved
 * \param dis2 Displacement calculated for second collider, if applicable
 * \param dt The delta time
 */
void collisionCases(Collider* col1, bool& mov1, BounceInfo& info1, Collider* col2, bool& mov2, BounceInfo& info2, float dt);
/**
 * Checks if two objects are on different teams
 * 
 * \param obj1 First Object
 * \param obj2 Second Object
 * \return True if the objects are on opposite teams, False if not
 */
bool oppositeTeams(GameObject* obj1, GameObject* obj2);
/**
 * Checks if shield is broken on their team
 *
 * \param obj GameObject to check
 * \return True if shield is broken, False if not
 */
//bool checkShield(GameObject* obj);

/**
 * generateExplosion Generates explosion particles when bullet kills a player.
 * \param obj The game object that emits the explosion.
 * \param dt The delta time
 */
void generateExplosion(GameObject* obj, float dt);

/**
 * generateDefense Generates defense reaction when bullet hits a player with shield.
 * \param obj The game object that emits the explosion.
 * \param dt The delta time
 */
void generateDefense(GameObject* obj1, GameObject* obj2, float dt);

/**
 * generateSpark Generates spark particles when bullet hits a wall.
 * \param obj The game object that emits the explosion.
 * \param dt The delta time
 */
void generateSpark(GameObject* obj, float dt);