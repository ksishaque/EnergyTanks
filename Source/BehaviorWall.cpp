/*****************************************************************//**
 * \file   BehaviorWall.cpp
 * \brief  Functions for managing the behavior of Walls
 *
 * \author Luke Tseng
 * \date   October 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
#define _USE_MATH_DEFINES
#include <cmath>
#include "GameObject.h"
#include "GraphicsUnit.h"
#include "LineCollider.h"
#include "MeshManager.h"
#include "Sprite.h"
#include "BehaviorWall.h"

BehaviorWall::BehaviorWall() : walls(), active(0), removed(false)
{
}

BehaviorWall::BehaviorWall(const BehaviorWall& behaviorWall)
{
}

BehaviorWall::~BehaviorWall()
{
}

void BehaviorWall::update(float dt)
{
	activateWalls();
}

Component* BehaviorWall::clone() const
{
    BehaviorWall* clone = new BehaviorWall();
	for(Wall wall : walls)
	{
		clone->walls.emplace_back(wall);
	}
    return clone;
}

//|LUKE|
void BehaviorWall::addWall(glm::vec3& p1, glm::vec3& p2)
{
	walls.emplace_back(p1, p2);
}

void BehaviorWall::addWall(Wall& w)
{
	walls.emplace_back(w);	//	Use copy constructor
}

void BehaviorWall::clearWall()
{
	walls.clear();
	removed = true;
}

void BehaviorWall::setParent(GameObject* parent)
{
	Component::setParent(parent);
	activateWalls();
}

void BehaviorWall::activateWalls()
{

	//	Check up-to-date case
	if(walls.size() == active)
	{
		return;
	}

	//	Get and check parent
	GameObject *par = getParent();
	if(par == nullptr)
	{
		return;
	}

	//	Get and check Sprite
	Sprite *spr = dynamic_cast<Sprite *>(par->get(ComponentTypeEnum::cSprite));
	if(spr == nullptr)
	{
		return;
	}

	//	Get or make LineCollider
	LineCollider *col = dynamic_cast<LineCollider *>(par->get(ComponentTypeEnum::cCollider));
	if(col == nullptr)
	{
		return;
	}

	//	Check case in which walls have been removed
	if (removed)
	{

		//	Clear LineCollider
		col -> clearSegments();

		//	Remove wall sprites
		for(unsigned i : graphicsIndices)
		{
			spr -> removeFromGraphics(i);
		}

		//	Reset active count
		active = 0;

	}

	//	Variable: Mesh to use
	Mesh *mesh;

	//	Check `mesh`
	if(!MeshManager::getInstance() -> getMesh(MeshManager::MeshType::single, mesh)) return;

	//	Add each wall to 
	for(; active < walls.size(); active += 1)
	{

		//	Get current wall
		glm::vec3 head = walls[active].first;
		glm::vec3 tail = walls[active].second;
		
		//	Activate current wall
		activateWall(head, tail, col, spr, mesh);

		//	Flip wall on x-axis
		head.x *= -1;
		tail.x *= -1;
		
		//	Activate current wall
		activateWall(head, tail, col, spr, mesh);

	}

}

void BehaviorWall::activateWall(glm::vec3& head, glm::vec3& tail, LineCollider* col, Sprite* spr, Mesh *mesh){
		
	//	Add to LineCollider
	col->addSegment(head, tail);

	//	Variable: Rotation of the line
	float rot = atan2f(head.x - tail.x, tail.y - head.y);

	//	Calculate `rot`
	rot *= 180;
	rot /= (float) M_PI;

	/*	Variables:
	trans: Displacement of the line
	len: Length of the line
	*/
	glm::vec3 trans = {(head.x + tail.x) / 2, (head.y + tail.y) / 2, 0};
	float len = glm::distance(head, tail);
	
	//	Create and add graphics
	spr -> addToGraphics(new GraphicsUnitMutable(mesh, nullptr, GraphicsUnit::Type::guWall1, nullptr, 0, 0, trans, glm::vec3(1, len, 1), rot, glm::vec4(0, 0, 0, 1)));
	spr -> addToGraphics(new GraphicsUnitMutable(mesh, nullptr, GraphicsUnit::Type::guWall2, nullptr, 0, 0, trans, glm::vec3(3, len + 2, 1), rot, glm::vec4(0, 0.75f, 0, 1)));

	//	Create glow effect
	for(unsigned i = 0; i < 15; i += 3) spr -> addToGraphics(new GraphicsUnitMutable(mesh, nullptr, GraphicsUnit::Type::guWall2, nullptr, 0, 0, trans, glm::vec3(3 + i, len + 2 + i, 1), rot, glm::vec4(0, 0.75f, 0, 0.125)));

}