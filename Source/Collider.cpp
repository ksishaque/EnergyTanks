/*!
\file Collider.cpp
\author Khaled S. Ishaque
\date 9-30-2022
\brief
	CPP file for class function definitions for Colliders
*/

#include "Collider.h"
#include "CollisionManager.h"

#include "BoxCollider.h"
#include "CircleCollider.h"
#include "LineCollider.h"
#include "GameObject.h"
#include "CollisionResolution.h"
#include "Trace.h"
/*!
 * @brief:
 * Default Constructor for Collider class
 * @param:
 * None
 * @return:
 * Nothing
 */
Collider::Collider(Type colType) :
	Component(ComponentTypeEnum::cCollider),
	type(colType), managerSet(false) {
#ifdef DEBUG_SYSTEM
	Trace::message("CTOR: Collider %p", this);
#endif
}
/*!
* @brief:
* Destructor for Collider class
* @param:
* None
* @return:
* Nothing
*/
Collider::~Collider() {
	if (managerSet)
	{
		CollisionManager::removeFromList(this);
	}
}
/*!
* @brief:
* set the type of collider that the component is
* @param:
* colType - the type to assign the collider component
* @return:
* Nothing
*/
Collider::Type Collider::getType() {
	return type;
}
/*!
* @brief:
* set the type of collider that the component is
* @param:
* colType - the type to assign the collider component
* @return:
* Nothing
*/
void Collider::setType(Type type) {
	this->type = type;
}

void Collider::debugDraw() {
	draw();
}

/*!
	* @brief:
	* Checks to see if any object's collider component is touching each other
	* @param:
    * collider1 - the first collider component to check the collision
    * info1 - the return reference for the displacement of the first collider
    * collider2 - the second collider component to check the collision
    * info2 - the return reference for the displacement of the second collider
	* @return:
	* TRUE if a collision was detected between the 2 colliders
	* FALSE if there is no collision happening between the 2 colliders
	*/
bool isColliding(Collider* collider1, BounceInfo& info1, Collider* collider2, BounceInfo& info2) {
	//null check
	if (collider1 && collider2) {
		//check the types of the colliders 
		if (collider1->type == Collider::Type::circle && collider2->type == Collider::Type::circle)
		{
			return collidingWithCircle(dynamic_cast<CircleCollider*>(collider1), info1, dynamic_cast<CircleCollider*>(collider2), info2);
		}
		if (collider1->type == Collider::Type::circle && collider2->type == Collider::Type::line)
		{
			return collidingWithLine(dynamic_cast<CircleCollider*>(collider1), info1, dynamic_cast<LineCollider*>(collider2));
		}
		if (collider1->type == Collider::Type::line && collider2->type == Collider::Type::circle)
		{
			return collidingWithLine(dynamic_cast<CircleCollider*>(collider2), info2, dynamic_cast<LineCollider*>(collider1));
		}
		if (collider1->type == Collider::Type::circle && collider2->type == Collider::Type::bounds)
		{
			return collidingWithBounds(dynamic_cast<CircleCollider*>(collider1), dynamic_cast<BoxCollider*>(collider2));
		}
		if (collider1->type == Collider::Type::bounds && collider2->type == Collider::Type::circle)
		{
			return collidingWithBounds(dynamic_cast<CircleCollider*>(collider2), dynamic_cast<BoxCollider*>(collider1));
		}
		if (collider1->type == Collider::Type::line && collider2->type == Collider::Type::bounds)
		{
			return false;
		}
		if (collider1->type == Collider::Type::line && collider2->type == Collider::Type::line)
		{
			return false;
		}
	}
	return false;
}

void Collider::update(float dt) {
	if (!managerSet)
	{
		CollisionManager::addToList(this);
		managerSet = true;
	}
}

bool checkCollision(Collider* collider1, Collider* collider2) {
	return false;//return collider1 -> isColliding(collider2);
}

