/*****************************************************************//**
 * \file   Component.cpp
 * \brief
 *
 * \author Luke Tseng
 * \date   September 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
#include "Component.h"
#include "GameObject.h"

Component::Component() : cType(ComponentTypeEnum::cInvalid), cParent(nullptr) {
}

Component::Component(ComponentTypeEnum type) :
	cType(type),
	cParent(nullptr)
{
}

Component::Component(const Component& comp) : Component(comp.cType){}

ComponentTypeEnum Component::getType() const
{
	return cType;
};

void Component::setParent(GameObject* parent)
{
	cParent = parent;
}

GameObject* Component::getParent()
{
	return cParent;
}

//|LUKE|
bool operator<(Component &left, Component &right)
{
	return left.cType < right.cType;
}