/*!
\file   ControlManager.h
\author Kevin Shin
\date   1-13-2023
\brief
		Functions for managing event-based inputs
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

class ControlManager;

#include <map>
#include <list>

#include "ISystem.h"

struct GLFWwindow;
class ActionList;
class ActionNode;
class Controller;
class ControlUnit;

/*!
\class  ControlManager
\brief
        System that manages event-based inputs
*/
class ControlManager : public ISystem{

	public:

		/*!
		\enum   KeyState
		          States in which the key may be in
		\var    KeyState::NONE
		          Key is not being held down
		\var    KeyState::PRESSED
		          Key is currently being pressed
		\var    KeyState::HELD
		          Key is being held down
		\var    KeyState::RELEASED
		          Key is currently being released
		\var    KeyState::INVALID
		          Key is not being held or released
		*/
		enum KeyState{PRESSED = 1, HELD = 2, RELEASED = 0, INVALID = -1};

		/*!
		\fn     static ControlManager *getInstance()
		\par    This function has no parameters.
		\return Singleton instance of the control manager
		\brief
		        This function retrieves the Singleton instance of the control manager.
		*/
		static ControlManager *getInstance();

		/*!
		\fn     static void closeInstance()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function closes the Singleton instance of the control manager.
		*/
		static void closeInstance();

		/*!
		\fn     void initialize() override
		\brief  See ISystem.h
		*/
		void initialize() override;

		/*!
		\fn     void update(float &dt) override
		\param  dt
		          dt
		\brief  See ISystem.h
		*/
		void update(float &dt) override;

		/*!
		\fn     void shutdown() override
		\brief  See ISystem.h
		*/
		void shutdown() override;

		/*!
		\fn     void addAction(ActionNode *node, int key, KeyState state)
		\param  node
		          Action node to activate
		\param  key
		          Key code for which the action should activate
		\param  state
		          State in which the key should be in when the action is activated
		\return Nothing
		\brief
		        This function adds an action to run in the case of a key event.
		*/
		void addAction(ActionNode *node, int key, KeyState state);

		/*!
		\fn!    void clearAction(int key, KeyState state)
		\param  key
		          Key code of actions to clear
		\param  state
		          State of key of actions to clear
		\return Nothing
		\brief
		        This function clears the actions tied to a key event.
		*/
		void clearAction(int key, KeyState state);

		/*!
		\fn     bool claimKey(int key)
		\param  key
		          Key code to check and claim
		\return If the key code was valid (i.e. unclaimed)
		\brief
		        This function checks if a key is valid and then claims it.
		*/
		bool claimKey(int key);

		/*!
		\fn     void reupdateKey(int key)
		\param  key
		          Key code to reupdate
		\return Nothing
		\brief
		        This function replays the "pressed" action of a key if applicable.
		*/
		void reupdateKey(int key);

		/*!
		\fn     bool checkKey(int key)
		\param  key
		          Key code to check
		\return If the key is pressed
		\brief
		        This function checks if a key is pressed.
		*/
		bool checkKey(int key);

		/*!
		\fn     void releaseKey(int key)
		\param  key
		          Key code to release
		\return Nothing
		\brief
		        This function releases the claim on a key.
		*/
		void releaseKey(int key);

		/*!
		\fn!    void universalInput(KeyState state)
		\param  key
		          Key code of actions to clear
		\param  state
		          State of key of actions to clear
		\return Nothing
		\brief
		        This function clears the actions tied to a key event.
		*/
		void universalInput(KeyState state);
		
		/*!
		\fn     bool setControllerUnit(int controller, ControlUnit *unit)
		\param  controller
		          Controller ID to set to
		\param  unit
		          Control unit to set
		\return Nothing
		\brief
		        This function mutates the control unit that a controller is using.
		*/
		bool setControllerUnit(int controller, ControlUnit *unit = nullptr);

		/*!
		\fn!    void manualControllerCall(int controller, KeyState state)
		\param  controller
		          Controller ID to manually call
		\param  state
		          Key state to manually call
		\return Nothing
		\brief
		        This function manually replicates any button calls if the button is pressed.
		*/
		void manualControllerCall(int controller, KeyState state);

		/*!
		\fn     friend void processKeyEvent(GLFWwindow* window, int key, int scancode,	int	action, int mods)
		\param  window
		          Handle of the window from which the key was pressed
		\param  key
		          Key code of the key pressed
		\param  scancode
		          Scan code of the key
		\param  action
		          Action affecting the key
		\param  mods
		          Modifier keys in play
		\return Nothing
		\brief
		        This function processes a key event.
		*/
		friend void processKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

		/*!
		\fn     friend void processJoystickEvent(GLFWwindow* window, int key, int scancode,	int	action, int mods)
		\param  joystick
		          Joystick that triggered the event
		\param  event
		          Event that occured
		\return Nothing
		\brief
		        This function processes a key event.
		*/
		friend void processJoystickEvent(int joystick, int event);

	private:

		/*!
		\var    instance
		          Singleton instance of the control manager
		*/
		static ControlManager *instance;

		/*!
		\var    window
		          Window handle to poll
		*/
		GLFWwindow *window;

		/*!
		\var    keyClaims
		          Claim values for each key
		*/
		bool *keyClaims;

		/*!
		\var    keyDowns
		          For each key, if it is down
		*/
		bool *keyDowns;

		/*!
		\var    keyActions
		          Action lists for each key
		*/
		ActionList **keyActions;

		/*!
		\var    controllers
		          Map of connected controllers and IDs
		*/
		std::map<int, Controller *> controllers;

		/*!
		\var    removedControllers
		          List of diconnected controller IDs
		*/
		std::list<int> removedControllers;

		/*!
		\fn     ControlManager()
		\par    This function has no parameters
		\return Newly constructed control manager
		\brief
		        This function constructs a new control manager.
		*/
		ControlManager();

		/*!
		\fn     ~ControlManager()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function deconstructs a control manager.
		*/
		~ControlManager();

};