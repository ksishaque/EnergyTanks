/*!
\file   LockStateAction.cpp
\author Kevin Shin
\date   4-7-2023
\brief
        Functions for creating and managing an action node for locking the gamestate
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "ObjectManager.h"

#include "LockStateAction.h"

/*!
\fn     LockStateAction::LockStateAction(bool lock)
\param  lock
          lock
\brief  See LockStateAction.h
*/
LockStateAction::LockStateAction(bool lock) : lock(lock){}

/*!
\fn     void LockStateAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void LockStateAction::operator()(GameObject *obj, float dt){

	//	Lock the gamestate
	ObjectManager::getInstance() -> lockState(lock);

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     LockStateAction *LockStateAction::clone() const
\brief  See LockStateAction.h
*/
LockStateAction *LockStateAction::clone() const{

	//	Variable: return value / clone of `this`
	LockStateAction *ans = new LockStateAction(lock);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}