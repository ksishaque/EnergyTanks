/*!
\file   SetObjectAction.cpp
\author Kevin Shin
\date   2-13-2023
\brief
        Functions for creating and managing an action node for setting a game object for future nodes
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "GameObject.h"
#include "ObjectContainer.h"
#include "ObjectManager.h"

#include "SetObjectAction.h"

/*!
\fn     SetObjectAction::SetObjectAction(const std::string &name)
\param  name
          name
\brief  See SetObjectAction.h
*/
SetObjectAction::SetObjectAction(const std::string &name) : ActionNode(), name(name){}

/*!
\fn     void SetObjectAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void SetObjectAction::operator()(GameObject *obj, float dt){

	//	Variable: Container to search for the new object
	ObjectContainer *man = nullptr;

	//	Find `man`
	if(obj) man = obj -> getManager();
	if(man == nullptr) man = ObjectManager::getInstance();

	//	Variable: New object to set
	GameObject *newObj = man -> findObject(name);

	//	Recursive call to `next`
	ActionNode::operator()(newObj, dt);

}

/*!
\fn     SetObjectAction *SetObjectAction::clone() const
\brief  See SetObjectAction.h
*/
SetObjectAction *SetObjectAction::clone() const{

	//	Variable: return value / clone of `this`
	SetObjectAction *ans = new SetObjectAction(name);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}