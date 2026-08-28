/*!
\file LineCollider.cpp
\author Khaled S. Ishaque
\date 9-27-2022
\brief
	CPP file for object LineCollider class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#include "LineCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"
#include "CircleCollider.h"
#include "CollisionResolution.h"
/*!
 * @brief:
 * Default Constructor for LineCollider class
 * @param:
 * None
 * @return:
 * Nothing
 */
LineCollider::LineCollider() :
    segments(0),
    Collider(Type::line) {
}
/*!
 * @brief:
 * Default Destructor for LineCollider class
 * @param:
 * None
 * @return:
 * Nothing
 */
LineCollider::~LineCollider() {
}
/*!
 * @brief:
 * Adds a line segment to a list in the line collider to check
 * @param:
 * point0 - first endpoint of a line
 * point1 - second endpoint of a line
 * @return:
 * Nothing
 */
void LineCollider::addSegment(glm::vec3 point0, glm::vec3 point1) {
	LineCollider* colliderLine = dynamic_cast<LineCollider*>(this);
	lineSegments line;
	line.lineSegment[0] = point0;
	line.lineSegment[1] = point1;
	colliderLine->segments.push_back(line);
}
/*!
 * @brief:
 * return the amount of lines in the list
 * @param:
 * None
 * @return:
 * The number of lines in the list
 */
unsigned int LineCollider::getLineCount() {
	return (unsigned)segments.size();
}
std::vector<LineCollider::lineSegments>& LineCollider::getSegment() {
	return segments;
}
/*!
 * @brief:
 * checks to see if the 2 colliders are touching each other
 * @param:
 * collider2 - the line collider to see if the line is in contact with another object
 * @return:
 * FALSE if the colliders are not touching each other
 */
bool collidingWithLine(CircleCollider* collider1, BounceInfo& info1, LineCollider* collider2) {
	//circle's transform and physics
	if(collider1 == nullptr || collider2 == nullptr) return false;
	GameObject* circleObject = collider1->getParent();
	Transform* circleTransform = dynamic_cast<Transform*>(circleObject->get(ComponentTypeEnum::cTransform));
	Physics* circlePhysics = dynamic_cast<Physics*>(circleObject->get(ComponentTypeEnum::cPhysics));
	//vectors of the translation
	glm::vec3 Bs = circlePhysics->getOldTransl();
	glm::vec3 Be = circleTransform->getTranslation();
	glm::vec3 v = Be - Bs;
	//line's endpoints
	LineCollider::lineSegments line;
	glm::vec3 p0, p1;
	//amount of lines
	unsigned int count = collider2->getLineCount();
	std::vector<LineCollider::lineSegments> segments = collider2->getSegment();
	float r = dynamic_cast<CircleCollider *>(collider1)->getRadius();
	//scores for earliest collision and non-bounce collisions
	bool ans = false;
	float minTi = 1.5f;
	for (unsigned int i = 0; i < count; ++i) {
		//get the segment and points
		line = segments[i];
		p0 = line.lineSegment[0];
		p1 = line.lineSegment[1];
		//edge vector and normalize
		glm::vec3 e = p0 - p1;
		glm::vec3 n;
		n.x = e.y;
		n.y = -e.x;
		n.z = 0;
		if (n != glm::vec3()) {
			n = glm::normalize(n);
		}
		//CircleCollider* cir = dynamic_cast<CircleCollider*>(collider1);
		//float d = glm::dot(n, p0 - Bs);
		//float r = cir->getRadius();
		//if (d > r || d < -r) {
		//	continue;
		//}

		float nBs = glm::dot(n, Bs);
		float nP0 = glm::dot(n, p0);
		/*
		if (nBs <= nP0 + r && nBs >= nP0 - r) {
			ans = true;
		}
		*/
		if (nBs < nP0 + r && nBs > nP0 - r) {
			float ti;
			BounceInfo temp1, temp2;
			if (collidingWithCircle(Bs, Be, temp1, p0, p0, temp2, r, ti) && ti < minTi) {
				ans = true;
				minTi = ti;
				info1 = temp1;
			}
			else if (collidingWithCircle(Bs, Be, temp1, p1, p1, temp2, r, ti) && ti < minTi) {
				ans = true;
				minTi = ti;
				info1 = temp1;
			}
			continue;
		}
		if (glm::dot(n, v) == 0) {
			continue;
		}
		float nBe = glm::dot(n, Be);
		if (nBs <= nP0 - r && nBe < nP0 - r) {
			continue;
		}
		if (nBs >= nP0 + r && nBe > nP0 + r) {
			continue;
		}
		float ti = nP0 - nBs;
		if (nBs > nP0) {
			ti += r;
		}
		else {
			ti -= r;
		}
		ti /= glm::dot(n, v);
		if (ti > minTi) {
			continue;
		}
		glm::vec3 Bi = Bs + v * ti;
		if (glm::dot((p1 - p0), (Bi - p0)) < 0) {
			BounceInfo temp1, temp2;
			if (collidingWithCircle(Bs, Be, temp1, p0, p0, temp2, r, ti) && ti < minTi) {
				ans = true;
				minTi = ti;
				info1 = temp1;
			}
			continue;
		}
		if (glm::dot((p0 - p1), (Bi - p1)) < 0) {
			BounceInfo temp1, temp2;
			if (collidingWithCircle(Bs, Be, temp1, p1, p1, temp2, r, ti) && ti < minTi) {
				ans = true;
				minTi = ti;
				info1 = temp1;
			}
			continue;
		}

		//reflect
		/*
		if (circleObject->getType() == GameObject::Bullet)
		{
			reflectLine(circleTransform, circlePhysics, n, Be, Bi);
		}
		else if (circleObject->getType() == GameObject::Player)
		{
			slideOnLine(circleTransform, circlePhysics, n, Be, Bi);
		}
		continue;
		*/

		//set bounce information
		ans = true;
		minTi = ti;
		info1.contact = Bi;
		ti -= 1;
		ti *= 2 * glm::dot(n, v);
		info1.distance = ti;
		info1.normal = n;
		info1.happen = true;
	}
	return ans;
}

/*!
 * @brief:
 * Clones a line collider component
 * @param:
 * None
 * @return:
 * The line collider component
 */
Component* LineCollider::clone() const {
	LineCollider* line = new LineCollider();
	line->segments = segments;
	return line;
}

//|Khaled|
void LineCollider::draw() {

}


//|KHALED|
void LineCollider::clearSegments() {
	segments.clear();
}