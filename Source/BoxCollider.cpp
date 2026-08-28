/*!
\file   BoxCollider.cpp
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   10-12-2022
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include <glm/glm.hpp>
#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "Renderer.h"
#include "MeshManager.h"
#include "Trace.h"
#include "GraphicsUnit.h"

#include "Window.h"

BoxCollider::BoxCollider() : Collider(Type::bounds), width(0), height(0)
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::setWidth(int w)
{
	width = w;
}

void BoxCollider::setHeight(int h)
{
	height = h;
}

int BoxCollider::getWidth(void)
{
	return width;
}

int BoxCollider::getHeight(void)
{
	return height;
}

bool collidingWithBounds(CircleCollider* collider1, BoxCollider* collider2)
{

	int width = collider2->getWidth();
	int height = collider2->getHeight();

	float radius = collider1->getRadius();
	if (width == 0 || height == 0) return false;
	GameObject* object1 = collider1->getParent();
	GameObject* object2 = collider2->getParent();
	Transform* trans1 = dynamic_cast<Transform*> (object1->get(ComponentTypeEnum::cTransform));
	Transform* trans2 = dynamic_cast<Transform*> (object2->get(ComponentTypeEnum::cTransform));
	if (trans1 == nullptr || trans2 == nullptr) return false;
	glm::vec3 pos1 = trans1->getTranslation();
	glm::vec3 pos2 = trans2->getTranslation();

	float closestX = glm::clamp(pos1.x, pos2.x - width / 2.0f, pos2.x + width / 2.0f);
	float closestY = glm::clamp(pos1.y, pos2.y - height / 2.0f, pos2.y + height / 2.0f);
	float distanceX = pos1.x - closestX;
	float distanceY = pos1.y - closestY;
	float distanceSquared = distanceX * distanceX + distanceY * distanceY;

	return distanceSquared <= radius * radius;

}

Component* BoxCollider::clone() const {
	BoxCollider* clone = new BoxCollider();
	clone->height = height;
	clone->width = width;
	clone->setType(bounds);
	return clone;
}

void BoxCollider::draw() {
    Mesh* mesh;
    MeshManager::getInstance()->getMesh(MeshManager::MeshType::single, mesh);
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
    glm::mat4 matrix = glm::translate(trans->getTranslation()) * glm::scale(glm::vec3(width, height, 1));
	Renderer::getInstance()->addToList(makeGraphicsUnit(mesh, matrix, GraphicsUnit::guDebug, nullptr, 0, 0, {1, 1, 0, 0.25f}));
}
