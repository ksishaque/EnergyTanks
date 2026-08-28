/*!
\file CollisionManager.cpp
\author Khaled S. Ishaque
\date 10-25-2022
\brief
    CPP file for object CollisionManager class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#include "CollisionManager.h"
#include "CollisionResolution.h"
#include "Trace.h"

CollisionManager* CollisionManager::instance = nullptr;

/*!
 * @brief:
 * Default Constructor for ColliderManager class
 * @param:
 * None
 * @return:
 * Nothing
 */
CollisionManager::CollisionManager() :
    ISystem(sCollide) {
}
/*!
 * @brief:
 * ISystem initializer for ColliderManager class
 * @param:
 * None
 * @return:
 * Nothing
 */
void CollisionManager::initialize() {

}
/*!
 * @brief:
 * Update function for ColliderManager class
 * @param:
 * None
 * @return:
 * Nothing
 */
void CollisionManager::update(float& dt) {
    for (unsigned i = 0; i + 1 < queue.size(); ++i) {
        for (unsigned j = i + 1; j < queue.size(); ++j) {
			BounceInfo dis1, dis2;
			if (isColliding(queue[i], dis1, queue[j], dis2)) {
				//Trace::message("Collision detected");
				bool mov1 = false, mov2 = false;
				collisionCases(queue[i], mov1, dis1, queue[j], mov2, dis2, dt);
				if (mov2)
				{
					recheck(j, dt);
				}
				if (mov1)
				{
					recheck(i, dt);
					break;
				}
			}
        }
    }
}
/*!
 * @brief:
 * ISystem shutdown for ColliderManager class
 * @param:
 * None
 * @return:
 * Nothing
 */
void CollisionManager::shutdown() {

}
/*!
 * @brief:
 * Adds a collider component to the back of the collider manager list
 * @param:
 * None
 * @return:
 * Nothing
 */
void CollisionManager::instanceAddToList(Collider* collider) {
    queue.push_back(collider);
#ifdef DEBUG_SYSTEM
	Trace::message("Added collider");
	for(Collider *col : queue) Trace::message("  %p", col);
#endif
}
/*!
 * @brief:
 * Gets the instance of the collision manager
 * @param:
 * None
 * @return:
 * Nothing
 */
void CollisionManager::instanceRemoveFromList(Collider* collider) {
    if (collider) {
		std::vector<Collider*>::iterator it = queue.begin();
		while(*it != collider) ++it;
        if(it != queue.end()) queue.erase(it);
#ifdef DEBUG_SYSTEM
		Trace::message("Removed collider");
		for(Collider *col : queue) Trace::message("  %p", col);
#endif
    }
}

CollisionManager* CollisionManager::getInstance() {
    if (instance == nullptr) {
        instance = new CollisionManager();
    }
    return instance;
}
/*!
 * @brief:
 * Closes the instance of the collision manager
 * @param:
 * None
 * @return:
 * Nothing
 */
void CollisionManager::closeInstance() {
    delete instance;
    instance = nullptr;
}
/*!
 * @brief:
 * Adds a collider to the collision manager list
 * @param:
 * None
 * @return:
 * Nothing
 */
void CollisionManager::addToList(Collider* collider) {
    if (instance == nullptr) {
        //Trace::message("CollisionManager instance is NULL");
        return;
    }
    instance->instanceAddToList(collider);
}
/*!
 * @brief:
 * Removes a collider in the collision manager list
 * @param:
 * None
 * @return:
 * Nothing
 */
void CollisionManager::removeFromList(Collider* collider) {
    if (instance == nullptr) {
        //Trace::message("CollisionManager instance is NULL");
        return;
    }
    instance->instanceRemoveFromList(collider);
}
/*!
 * @brief:
 * Re-checks a collider with every other collider for ColliderManager class
 * @param:
 * None
 * @return:
 * Nothing
 */
void CollisionManager::recheck(unsigned i, float dt, unsigned count) {
	if(count > 64) return;
    for (unsigned j = 0; j < queue.size(); ++j) {
		BounceInfo dis1, dis2;
		if (i != j && isColliding(queue[i], dis1, queue[j], dis2)) {
			//Trace::message("Collision detected");
			bool mov1 = false, mov2 = false;
			collisionCases(queue[i], mov1, dis1, queue[j], mov2, dis2, dt);
			if (mov2)
			{
				recheck(j, dt, count + 1);
			}
			if (mov1)
			{
				recheck(i, dt, count + 1);
				return;
			}
		}
    }
}