/*!
\file   MenuOption.h
\author Kevin Shin
\date   4-2-2023
\brief
        Functions for creating and managing a selection menu option
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

class MenuOption;

#include <glm/glm.hpp>

#include "ControlUnit.h"

class BehaviorOptionSelector;
class GameObject;
class Transform;

/*!
\class  MenuOption
\brief
        Option in a selection menu
*/
class MenuOption{
	public:

		/*!
		\fn     MenuOption()
		\par    This function takes no parameters.
		\return Constructed action list
		\brief
		        This function constructs a new option.
		*/
		MenuOption();

		/*!
		\fn     MenuOption(const MenuOption &source)
		\param  source
		          Option to copy
		\return Constructed action list
		\brief
		        This function constructs a new option by copying an existing option.
		*/
		MenuOption(const MenuOption &source);

		/*!
		\fn     ~MenuOption()
		\par    This function takes no parameters.
		\return Nothing
		\brief
		        This function deconstructs an option.
		*/
		~MenuOption();

		/*!
		\fn     void setAction(ControlUnit::ControlType type, ControlManager::KeyState keyState, ActionList *action)
		\param  type
		          Control input to set the action to
		\param  keyState
		          State of the control input to set the action to
		\param  action
		          Action list to set
		\return Nothing
		\brief
		        This function mutates the action list to activate to a given control input.
		*/
		void setAction(ControlUnit::ControlType type, ControlManager::KeyState keyState, ActionList *action);

		/*!
		\fn     void setTransform(const glm::vec3 &translation, const glm::vec3 &scale, float rotation)
		\param  translation
		          Translation to set
		\param  scale
		          Scale to set
		\param  rotation
		          Rotation
		\return Nothing
		\brief
		        This function mutates the transformation of any selector on the option.
		*/
		void setTransform(const glm::vec3 &translation, const glm::vec3 &scale, float rotation);

		/*!
		\fn     void placeSelector(GameObject *selector) const
		\param  selector
		          Selector object to set
		\return Nothing
		\brief
		        This function mutates a selector to align with the current option.
		*/
		void placeSelector(GameObject *selector) const;

		/*!
		\fn     void select(GameObject *selector, ControlUnit::ControlType action, ControlManager::KeyState keyState)
		\param  selector
		          Selector object that is selecting from the option
		\param  action
		          Control input that was used
		\param  keyState
		          State of the control input that was used
		\param  dt
		          Time since previous frame
		\return Nothing
		\brief
		        This function activates an action based on a selector's control inputs.
		*/
		void select(GameObject *selector, ControlUnit::ControlType action, ControlManager::KeyState keyState, float dt);

	private:

		/*!
		\var    trans
		          Transition to set the selector to
		*/
		Transform *trans;

		/*!
		\var    actions
		          Actions for the selector to take depending on keystroke
		*/
		ActionList *actions[CONTROL_UNIT_KEY_MAX][3];

};