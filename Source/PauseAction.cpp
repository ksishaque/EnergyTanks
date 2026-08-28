/*!
\file   PauseAction.cpp
\author Kevin Shin
\date   4-10-2023
\brief
        Functions for creating and managing an action nodes for pausing and unpausing the game
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "PauseSystem.h"

#include "PauseAction.h"

/*!
\fn     void PauseAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void PauseAction::operator()(GameObject *obj, float dt){

	//	Recursive call to next
	PauseSystem::getInstance() -> pause(true);

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     PauseAction *PauseAction::clone() const
\brief  See PauseAction.h
*/
PauseAction *PauseAction::clone() const{

	//	Variable: return value / clone of `this`
	PauseAction *ans = new PauseAction();

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}

/*!
\fn     void UnpauseAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void UnpauseAction::operator()(GameObject *obj, float dt){

	//	Recursive call to next
	PauseSystem::getInstance() -> pause(false);

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     UnpauseAction *UnpauseAction::clone() const
\brief  See PauseAction.h
*/
UnpauseAction *UnpauseAction::clone() const{

	//	Variable: return value / clone of `this`
	UnpauseAction *ans = new UnpauseAction();

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}