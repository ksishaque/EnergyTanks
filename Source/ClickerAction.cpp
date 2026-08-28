/*!
\file   ClickerAction.cpp
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for creating and managing an action node for producing a consistent testing sound effect
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "SoundSystem.h"

#include "ClickerAction.h"

/*!
\fn     void ClickerAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void ClickerAction::operator()(GameObject *obj, float dt){

	//	Click
	SoundSystem::getInstance() -> click();

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     ClickerAction *ClickerAction::clone() const
\brief  See ActionNode.h
*/
ClickerAction *ClickerAction::clone() const{

	//	Variable: return value / clone of `this`
	ClickerAction *ans = new ClickerAction();

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}