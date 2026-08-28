/*!
\file   ControlUnitAction.h
\author Kevin Shin
\date   2-13-2023
\brief
        Functions for creating and managing an action node for updating a `BehaviorControllable`
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class ControlUnitAction;

#include <string>

#include "ActionNode.h"
#include "ControlUnit.h"

/*!
\class  ControlUnitAction
\brief
        Nodes in an action list that updates an axis of a controllable object behavior
*/
class ControlUnitAction : public ActionNode{
	public:

		/*!
		\fn     ControlUnitAction(ControlUnit *unit, ControlUnit::ControlType action, ControlManager::KeyState state)
		\param  unit
		          Control unit to notify
		\param  action
		          Action to call
		\param  state
		          State of key to report
		\return Newly constructed control action
		\brief
		        This function constructs a new control node.
		*/
		ControlUnitAction(ControlUnit *unit, ControlUnit::ControlType action, ControlManager::KeyState state);

		/*!
		\fn     void operator()(GameObject *object, float dt)
		\param  object
		          object
		\param  dt
		          dt
		\brief  See ActionNode.h
		*/
		void operator()(GameObject *object, float dt);

		/*!
		\fn     ControlUnitAction *clone() const
		\brief  See ActionNode.h
		*/
		ControlUnitAction *clone() const;

	private:

		/*!
		\var    unit
		          Control unit to notify
		*/
		ControlUnit *unit;

		/*!
		\var    action
		          Action to call
		*/
		ControlUnit::ControlType action;

		/*!
		\var    state
		          State of key to report
		*/
		ControlManager::KeyState state;

};