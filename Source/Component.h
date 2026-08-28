/*****************************************************************//**
 * \file   Component.h
 * \brief
 *
 * \author Luke Tseng
 * \author
 * \date   September 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
#pragma once
//#include "GameObject.h"
typedef class GameObject GameObject, * GameObjectPtr;

enum class ComponentTypeEnum
{
	cBehavior, cActionList, cPhysics, cSprite, cCollider, cTransform, cCount, cInvalid
};

class Component {
public:
	/**
	 * Default constructor
	 * 
	 */
	Component();
	/**
	 * Constructor that sets type
	 * 
	 * \param type The type of component to set to
	 */
	Component(ComponentTypeEnum type);
	/**
	 * Copy constructor
	 * 
	 * \param comp Component to copy
	 */
	Component(const Component& comp);
	/**
	 * Destructor
	 * 
	 */
	virtual ~Component(){}
	/**
	 * Gets type of component
	 * 
	 * \return Type of component
	 */
	ComponentTypeEnum getType() const;
	/**
	 * Sets component to a parent
	 * 
	 * \param Parent GameObject to set to
	 */
	virtual void setParent(GameObject* parent);
	/**
	 * Gets parent of component
	 * 
	 * \return GameObject of component
	 */
	GameObject* getParent();
	virtual Component* clone() const = 0;
	virtual void update(float dt) {};
    virtual void debugDraw() {};
	//|LUKE|
	friend bool operator<(Component& left, Component& right);
private:
	ComponentTypeEnum cType;
	GameObject* cParent;
};