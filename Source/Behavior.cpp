/*!
\file   Behavior.cpp
\author Kevin Shin
\date   10-4-2022
\brief
        Functions for managing a behavior
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "Behavior.h"

/*!
\fn     Behavior::Behavior()
\brief  See Behavior.h
*/
Behavior::Behavior() : Component(ComponentTypeEnum::cBehavior), physics(nullptr){}

/*!
\fn     void Behavior::setPhysics(Physics *phys)
\param  phys
          physics
\brief  See Behavior.h
*/
void Behavior::setPhysics(Physics *phys){
	physics = phys;
}

/*!
\fn     Physics *Behavior::getPhysics()
\brief  See Behavior.h
*/
Physics *Behavior::getPhysics(){
	return physics;
}

/*!
\fn     Behavior::Behavior(const Behavior &that)
\param  that
          source
\brief  See Behavior.h
*/
Behavior::Behavior(const Behavior &that) : Component(ComponentTypeEnum::cBehavior), physics(nullptr){}