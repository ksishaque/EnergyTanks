/*!
\file   ControlUnitAction.cpp
\author Kevin Shin
\date   2-13-2023
\brief
        Functions for creating and managing an action node for updating a `BehaviorControllable`
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "ControlUnitAction.h"

/*!
\fn     ControlUnitAction::ControlUnitAction(ControlUnit *u, ControlUnit::ControlType act, ControlManager::KeyState state)
\param  u
          unit
\param  act
          action
\param  state
          state
\brief  See ControlUnitAction.h
*/
ControlUnitAction::ControlUnitAction(ControlUnit *u, ControlUnit::ControlType act, ControlManager::KeyState state) : ActionNode(), unit(u), action(act), state(state){}

/*!
\fn     void ControlUnitAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void ControlUnitAction::operator()(GameObject *obj, float dt){
	 
	//	Notify `behavior`
	if(unit) unit -> actionCall(action, state);

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     ControlUnitAction *ControlUnitAction::clone() const
\brief  See ControlUnitAction.h
*/
ControlUnitAction *ControlUnitAction::clone() const{

	//	Variable: return value / clone of `this`
	ControlUnitAction *ans = new ControlUnitAction(unit, action, state);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}