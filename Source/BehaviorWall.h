/*****************************************************************//**
 * \file   BehaviorWall.h
 * \brief  Header for BehaviorWall.cpp
 *
 * \author Luke Tseng
 * \date   October 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
#pragma once
#include "glm/glm.hpp"
#include <utility>
#include <vector>
#include "Behavior.h"

typedef std::pair<glm::vec3, glm::vec3> Wall;

class LineCollider;
class Sprite;
class Mesh;

class BehaviorWall : public Behavior
{
public:
    /**
    * Constructor for BehaviorWall
    *
    */
    BehaviorWall();
    /**
     * Copy Constructor for BehaviorWall
     *
     */
    BehaviorWall(const BehaviorWall& behaviorWall);
    /**
     * Destructor for BehaviorWall
     *
     */
    ~BehaviorWall();
    /**
     * Update function for BehaviorWall
     *
     */
    void update(float dt);
    /**
     * Clone function for BehaviorWall
     *
     */
    Component* clone() const override;
    /**
     * Function to set parent object
     *
     */
    void setParent(GameObject* parent) override;
    /**
     * Function to add a wall
     *
     */
    void addWall(glm::vec3& point1, glm::vec3& point2);
    /**
     * Function to add a wall
     *
     */
    void addWall(Wall &wall);
    /**
     * Function to remove all walls
     *
     */
    void clearWall();
private:
    /**
     * Function to add walls to Sprite and LineCollider
     *
     */
    void activateWalls();
    /**
     * Function to add a single wall to Sprite and LineCollider
     *
     */
    void activateWall(glm::vec3& point1, glm::vec3& point2, LineCollider* collider, Sprite* sprite, Mesh* mesh);
    /**
     * List of walls
     *
     */
	std::vector<Wall> walls;
    /**
     * Number of walls added to Sprite and LineCollider
     *
     */
	size_t active;
    /**
     * Flag for when a wall is removed
     *
     */
	bool removed;
    /**
     * Indices of graphics units in Sprite
     *
     */
	std::vector<unsigned> graphicsIndices;
};
