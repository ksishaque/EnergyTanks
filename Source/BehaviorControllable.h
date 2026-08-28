/*!
\file   BehaviorControllable.h
\author Kevin Shin
\date   2-13-2023
\brief
        Functions for managing the behavior of a player-controlled object
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

class BehaviorControllable;

#include "Behavior.h"
#include "ControlUnit.h"

class BehaviorControllable : public Behavior{
	public:

		/*!
		\fn     BehaviorControllable()
		\par    This function has no parameters.
		\return Constructed controllable object behavior
		\brief
		        This function constructs a new behavior for a player-controlled object.
		*/
		BehaviorControllable();

		/*!
		\fn     ~BehaviorControllablle()
		\par    This function has no parameters
		\return Nothing
		\brief
		        This function decontructs a controllable object behavior.
		*/
		~BehaviorControllable();

		/*!
		\fn     void update(float dt)
		\param  dt
		          dt
		\brief  See Component.h
		*/
		void update(float dt);

		/*!
		\fn     void setPriority(int priority)
		\param  priority
		          Priority level to set
		\return Nothing
		\brief
		        This function mutates a controllable object's priority level.
		*/
		void setPriority(int priority);

		/*!
		\fn     int getPriority()
		\par    This function has no parameters.
		\return Priority level of the controllable object
		\brief
		        This function accesses a controllable object's priority level.
		*/
		int getPriority();

		/*!
		\fn     void setControlUnit(ControlUnit *unit)
		\param  unit
		          Control unit to set
		\return Nothing
		\brief
		        This function mutates a controllable object's control unit.
		*/
		void setControlUnit(ControlUnit *unit);

		/*!
		\fn     ControlUnit *getControlUnit()
		\par    This function has no parameters.
		\return Control unit in use
		\brief
		        This function accesses a controllable object's control unit.
		*/
		ControlUnit *getControlUnit();

		/*!
		\fn     ControlUnit releasetControlUnit()
		\par    This function has no parameters.
		\return Control unit in use
		\brief
		        This function releases a controllable object's control unit.
		*/
		ControlUnit *releaseControlUnit();

		/*!
		\fn     void actionCall(ControlUnit::ControlType action, ControlManager::KeyState keyState)
		\param  action
		          ID of the action to call
		\param  keyState
		          State of the key
		\return Nothing
		\brief
		        This function preforms an action when an action key is pressed.
		*/
		virtual void actionCall(ControlUnit::ControlType action, ControlManager::KeyState keyState = ControlManager::KeyState::HELD) = 0;

	protected:

		/*!
		\fn     virtual void gainControl()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function initializes anything that needs to be set when the behavior gains a control unit.
		*/
		virtual void gainControl(){}

		/*!
		\fn     virtual void loseControl()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function initializes anything that needs to be set when the behavior releases a control unit.
		*/
		virtual void loseControl(){}
        
	private:

		/*!
		\var    deleting
		          If the behavior is currently deleting itself
		*/
		bool deleting;

		/*!
		\var    teamSet
		          If the team has been updated
		*/
		bool teamSet;

		/*!
		\var    hadControl
		          If the behavior has had control before
		*/
		bool hadControl;

		/*!
		\var    priority
		          Priority level for controls (highest priority level gets control)
		*/
		int priority;

		/*!
		\var    controls
		          Control unit used to control the behavior
		*/
		ControlUnit *controls;

};
