/*!
\file   ISystem.cpp
\author Kevin Shin (kevin.shin\@digipen.edu)
        Benedict Yau (benedict.yau\@digipen.edu)
\date   9-9-2022
\brief
        Functions for managing a sprite
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "ISystem.h"

/*!
\fn     void ISystem::setParent(ISystem *parent)
\param  parent
          parent
\brief  See ISystem.h
*/
void ISystem::setParent(ISystem* parent) 
{
    cParent = parent;
}

/*!
\fn     ISystem *ISystem::getParent() const
\brief  See ISystem.h
*/
ISystem* ISystem::getParent() const
{
    return cParent;
}

/*!
\fn     ISystem::Type ISystem::getType()
\brief  See ISystem.h
*/
ISystem::Type ISystem::getType() const 
{
	return type;
}

/*!
\fn     bool operator>(ISystem a, ISystem b)
\param  a
          sys1
\param  b
          sys2
\brief  See ISystem.h
*/
bool operator<(ISystem &a, ISystem &b)
{
	return a.type < b.type;
}

/*!
\fn     ISystem::ISystem(Type type)
\param  type
          type
\brief  See ISystem.h
*/
ISystem::ISystem(Type type) : type(type){}

/*!
\fn     void ISystem::initialize()
\brief  See ISystem.h
*/
void ISystem::initialize(){
	active = true;
}

/*!
\fn     void ISystem::shutdown()
\brief  See ISystem.h
*/
void ISystem::shutdown(){
	active = false;
}

/*!
\fn     bool ISystem::isActive() const
\brief  See ISystem.h
*/
bool ISystem::isActive() const{
	return active;
}

/*!
\fn     ISystem::~ISystem()
\brief  See ISystem.h
*/
ISystem::~ISystem(){
	if(active) shutdown();
}