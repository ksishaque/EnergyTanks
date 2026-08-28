/*!
\file   ControlUnit.h
\author Kevin Shin
\date   3-17-2023
\brief
        Functions for managing a player's control scheme
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

class ControlUnit;

#define CONTROL_UNIT_KEY_MAX (unsigned) ControlUnit::ControlType::MAX

#include "ControlManager.h"

class BehaviorControllable;

/*!
\class  ControlUnit
\brief  Container that claims and manages a player's control scheme
*/
class ControlUnit{
	public:

		/*!
		\enum   ControlType
		          Type of input mapped to a key
		\var    INVALID
		          Minimum / invalid input
		\var    UP
		          Up input
		\var    DOWN
		          Down input
		\var    LEFT
		          Left input
		\var    RIGHT
		          Right input
		\var    FIRST
		          First input
		\var    SECOND
		          Second input
		\var    MAX
		          Maximum number of controls
		\var    Y_NEUTRAL
		          Value suggesting that the y-axis is neutral
		\var    X_NEUTRAL
		          Value suggesting that the x-axis is neutral
		*/
		enum ControlType{INVALID = -1, UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, FIRST = 4, SECOND = 5, MAX = 6, Y_NEUTRAL = 7, X_NEUTRAL = 8};

		/*!
		\fn     ControlUnit(int up, int down, int left, int right, int first, int second)
		\param  up
		          Key code for up input; Defaulted to GLFW_KEY_UP
		\param  down
		          Key code for down input; Defaulted to GLFW_KEY_DOWN
		\param  left
		          Key code for left input; Defaulted to GLFW_KEY_LEFT
		\param  right
		          Key code for right input; Defaulted to GLFW_KEY_RIGHT
		\param  first
		          Key code for first action input; Defaulted to GLFW_KEY_SPACE
		\param  second
		          Key code for second action input; Defaulted to GLFW_KEY_ESCAPE
		\return Constructed control unit
		\brief
		        This function constructs a new behavior for a player control unit.
		*/
		ControlUnit(int up = 265, int down = 264, int left = 263, int right = 262, int first = 32, int second = 256);

		/*!
		\fn     ~ControlUnit()
		\par    This function has no parameters
		\return Nothing
		\brief
		        This function decontructs a control unit.
		*/
		~ControlUnit();

		/*!
		\fn     void update()
		\par    This function has no parameters
		\return Nothing
		\brief
		        This function attempts to claim any unclaimed keys in a control unit, then calls any function calls for directional input.
		*/
		void update();

		/*!
		\fn     void setKey(ControlType control, int key)
		\param  control
		          Control to mutate the key for
		\param  key
		          Key code for input
		\return Nothing
		\brief
		        This function mutates a control unit's key input for a given control.
		*/
		void setKey(ControlType control, int key);

		/*!
		\fn     int getKey(ControlType control) const
		\param  control
		          Control to access the key for
		\return Up input of the controllable object behavior
		\brief
                This function accesses a controllable object behavior's designated up input.
		*/
		int getKey(ControlType control) const;

		/*!
		\fn     const int *getKeyReference(ControlType control) const
		\param  control
		          Control to access the key for
		\return Up input of the controllable object behavior
		\brief
                This function accesses a controllable object behavior's designated up input.
		*/
		const int *getKeyReference(ControlType control) const;

		/*!
		\fn     bool setBehavior(BehaviorControllable *behavior)
		\param  behavior
		          Behavior to set
		\return If `behavior` was successfully set
		\brief
		        This function mutates which behavior is using the control unit.
		*/
		bool setBehavior(BehaviorControllable *behavior);

		/*!
		\fn     bool setBehavior(bool update)
		\param  If the function should skip reupdating the old behavior
		\return `true`
		\brief
		        This function resets which behavior is using the control unit.
		*/
		bool setBehavior(bool update = false);

		/*!
		\fn     void setController(int controller)
		\param  controller
		          Controller ID to set
		\return Nothing
		\brief
		        This function sets the control unit's cooresponding controller ID.
		*/
		void setController(int controller);

		/*!
		\fn     void iterateAxisY(int value)
		\param  value
		          Value to iterate by
		\return Nothing
		\brief
		        This function iterates the up-down control state of the  control unit.
		*/
		void iterateAxisY(int value);

		/*!
		\fn     void iterateAxisX(int value)
		\param  value
		          Value to iterate by
		\return Nothing
		\brief
		        This function iterates the left-right control state of the  control unit.
		*/
		void iterateAxisX(int value);

		/*!
		\class  ControlUnitAction
		\brief  See ControlBehaviorAction.h
		*/
		friend class ControlUnitAction;

		/*!
		\fn     void actionCall(ControlType action, ControlManager::KeyState keyState)
		\param  action
		          ID of the action to call
		\param  keyState
		          State of the key
		\return Nothing
		\brief
		        This function preforms an action when an action key is pressed.
		*/
		void actionCall(ControlType action, ControlManager::KeyState keyState);
        
	private:

		/*!
		\var    inUD
		          Up-down control state
		\var    inLR
		          Left-right control state
		*/
		int inUD;
		int inLR;

		/*!
		\var   keys
		          Key codes for input
		\var   visKeys
		          Key codes to display
		\var   contKeys
		          Key codes to display for controllers
		*/
		int keys[CONTROL_UNIT_KEY_MAX], visKeys[CONTROL_UNIT_KEY_MAX];
		static int contKeys[CONTROL_UNIT_KEY_MAX];

		/*!
		\var    claim
		          If each key has been claimed
		\var    fullClaim
		          If all keys have been claimed
		*/
		bool claims[CONTROL_UNIT_KEY_MAX], fullClaim;

		/*!
		\var    behavior
		          Behavior to control
		*/
		BehaviorControllable *behavior;

		/*!
		\var    controller
		          ID for any connected controller
		*/
		int controller;

		/*!
		\fn     void attemptClaim(int key, bool &claim, ControlType action)
		\param  key
		          Key to try to claim
		\param  claim
		          Claim value to update
		\param  action
		          Action ID to set
		\return Nothing
		\brief
		        This function attempts to claim an action key.
		*/
		void attemptClaim(int key, bool &claim, ControlType action);

		/*!
		\fn     void attemptClaim(int key, bool &claim, ControlType action, int &axis, int value)
		\param  key
		          Key to try to claim
		\param  claim
		          Claim value to update
		\param  action
		          Action ID to set
		\param  axis
		          Axis to add to
		\param  value
		          Value to add
		\return Nothing
		\brief
		        This function attempts to claim an directional action key.
		*/
		void attemptClaim(int key, bool &claim, ControlType action, int &axis, int value);

};
