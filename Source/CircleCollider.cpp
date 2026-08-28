/*!
\file CircleCollider.cpp
\author Khaled S. Ishaque
\date 9-23-2022
\brief
    CPP file for object CircleCollider class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#include "CircleCollider.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "CollisionResolution.h"
#include "GameObject.h"
#include "General.h"
#include "MeshManager.h"
#include "GraphicsUnit.h"
#include "Physics.h"
#include "Renderer.h"
#include "TextureManager.h"
#include "Trace.h"
#include "Transform.h"
//#include "Component.h"

/*!
 * @brief:
 * Default Constructor for CircleCollider class
 * @param:
 * None
 * @return:
 * Nothing
 */
CircleCollider::CircleCollider() :
    Collider(Type::circle),
    radius(1.0f) {
}

/*!
 * @brief:
 * Default Destructor for CircleCollider class
 * @param:
 * None
 * @return:
 * Nothing
 */
CircleCollider::~CircleCollider() {
}

/*!
 * @brief:
 * gets the radius of the circle for the collider
 * @param:
 * None
 * @return:
 * the value of the radius
 */
float CircleCollider::getRadius() {
    return radius;
}

/*!
 * @brief:
 * sets the radius of the circle for the collider
 * @param:
 * newRadius - the new radius of the circle
 * @return:
 * Nothing
 */
void CircleCollider::setRadius(float newRadius) {
    radius = newRadius;
}

/*!
 * @brief:
 * Draws a mesh that will be a visualizer for the collider
 * @param:
 * None
 * @return:
 * Nothing
 */
void CircleCollider::draw() {
    Mesh* mesh;
    MeshManager::getInstance()->getMesh(MeshManager::MeshType::circle, mesh);
    GameObject* parent = getParent();
    if (!parent) {
#ifdef DEBUG_SYSTEM
        Trace::error("DEBUG DRAW: Parent is missing");
#endif
        return;
    }
    Transform* trans = dynamic_cast<Transform*>(parent->get(ComponentTypeEnum::cTransform));
    if (!trans) {
#ifdef DEBUG_SYSTEM
        Trace::error("DEBUG DRAW: Transform is missing");
#endif
        return;
    }
    glm::mat4 matrix = glm::translate(trans->getTranslation()) * glm::scale(glm::vec3(2 * radius, 2 * radius, 1));
	Renderer::getInstance()->addToList(makeGraphicsUnit(mesh, matrix, GraphicsUnit::guDebug, nullptr, 0, 0, {1, 1, 0, 0.25f}));
}

/*!
 * @brief:
 * checks and calculates bounce information
 * @param:
 * colPos - The position at which the collision occured
 * final - The final position if the collider did not bounce
 * n - The normal vector of the collision
 * info - The bounce reference to put details into
 * @return:
 * Nothing
 */
static void calculateBounce(const glm::vec3& colPos, const glm::vec3& final, const glm::vec3& n, BounceInfo& info){
	/*check dot product*/
	float product = glm::dot(colPos - final, n);
	if (product > 0) {
		/*record bounce*/
		info.happen = true;
		info.distance = product * 2;
		info.contact = colPos;
		info.normal = n;
	}
}

/*!
 * @brief:
 * checks to see if 2 circles are touching each other
 * @param:
 * collider1 - The first collider to cast to a circle collider
 * info1 - The bounce reference to put details into
 * collider2 - The second collider to cast to a circle collider
 * info2 - The bounce reference to put details into
 * @return:
 * TRUE if the distance between the 2 circles are less than their radii combined
 * FALSE if the distance between is larger than the combined radii
 */
bool collidingWithCircle(CircleCollider* collider1, BounceInfo& info1, CircleCollider* collider2, BounceInfo& info2) {
    /*get the game objects of the colliders*/
	if (collider1 == nullptr || collider2 == nullptr) return false;
    GameObject* object1 = collider1->getParent();
    GameObject* object2 = collider2->getParent();
    /*get the transform parts of the game objects*/
    Transform* transformObj1 = dynamic_cast<Transform*>
        (object1->get(ComponentTypeEnum::cTransform));
    Transform* transformObj2 = dynamic_cast<Transform*>
        (object2->get(ComponentTypeEnum::cTransform));
	if(transformObj1 == nullptr || transformObj2 == nullptr) return false;
    /*get the physics parts of the game objects*/
    Physics* physicsObj1 = dynamic_cast<Physics*>
        (object1->get(ComponentTypeEnum::cPhysics));
    Physics* physicsObj2 = dynamic_cast<Physics*>
        (object2->get(ComponentTypeEnum::cPhysics));
    /*cast the colliders to circle colliders*/
    /*get the current translations and make the squared distance between the 2 translations*/
    glm::vec3 posObj1 = transformObj1->getTranslation();
    glm::vec3 posObj2 = transformObj2->getTranslation();
    //float distance = glm::distance(posObj1, posObj2) * glm::distance(posObj1, posObj2);
#if 0
    float distance = glm::distance(posObj1, posObj2);
    /*get the radii, square them, and get the combined value of the 2*/
    float radius1 = collider1->getRadius();
    float radius2 = collider2->getRadius();
    //float squaredRadius = (radius1 + radius2) * (radius1 + radius2);
    float squaredRadius = radius1 + radius2;
    /*check to see if the circles are touching each other*/
    if (distance <= squaredRadius) {
        return true;
    }
    return false;
#endif
    /*get the previous translations*/
    glm::vec3 prePosObj1 = posObj1;
	if (physicsObj1) {
		prePosObj1 = physicsObj1->getOldTransl();
	}
    glm::vec3 prePosObj2 = posObj2;
	if (physicsObj2) {
		prePosObj2 = physicsObj2->getOldTransl();
	}
	/*get total radius*/
	float radii = collider1->getRadius() + collider2->getRadius();
	float temp;
	/*check if one is stationary*/
	return collidingWithCircle(prePosObj1, posObj1, info1, prePosObj2, posObj2, info2, radii, temp);
}

Component* CircleCollider::clone() const {
    CircleCollider* clone = new CircleCollider();
    clone->radius = radius;
    clone->setType(circle);
    return clone;
}

/*!
 * @brief:
 * checks to see if 2 circles are touching each other
 * @param:
 * start - The initial position of the moving circle
 * end - The final position of the moving circle
 * radius - The combined radius of the two circles
 * info - The bounce reference to put details into
 * point - The position of the static circle
 * info - The reference to put the time of collision into
 * @return:
 * TRUE if the distance between the 2 circles are less than their radii combined
 * FALSE if the distance between is larger than the combined radii
 */
bool collidingWithCircle(const glm::vec3& start1, const glm::vec3& end1, BounceInfo& info1, const glm::vec3& start2, const glm::vec3& end2, BounceInfo& info2, float radii, float& i) {
	/*setup i*/
	i = -1;
	/*check radius*/
	if (radii == 0) {
		return false;
	}
	/*get vector between starting points*/
	glm::vec3 dStart = start1 - start2;
	/*check escape case*/
	if((dStart.x * dStart.x) + (dStart.y * dStart.y) <= radii * radii) return true;
	/*get the movements*/
	glm::vec3 vel1 = end1 - start1;
	glm::vec3 vel2 = end2 - start2;
	/*get vector between velocities*/
	glm::vec3 dVel = vel1 - vel2;
	/*find time of collision*/
	if (!quadraticFormula((dVel.x * dVel.x) + (dVel.y * dVel.y), 2 * ((dStart.x * dVel.x) + (dStart.y * dVel.y)), (dStart.x * dStart.x) + (dStart.y * dStart.y) - (radii * radii), i)) {
		return false;
	}
	/*check if i is outside the valid interval*/
	if (i <= 0 || i > 1) {
		return false;
	}
	/*calculate collision positions*/
	glm::vec3 colPos1 = start1 + vel1 * i;
	glm::vec3 colPos2 = start2 + vel2 * i;
	/*calculate collision normal*/
	dStart = colPos1 - colPos2;
	dStart /= radii;
	/*get bounce information*/
	calculateBounce(colPos1, end1, dStart, info1);
	calculateBounce(colPos2, end2, -dStart, info2);
 	return true;
}