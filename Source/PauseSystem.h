/*!
\file   PauseSystem.h
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   4-9-2023
\brief
        Functions for creating and maintaining a pause system
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

class PauseSystem;

#include "ISystem.h"

struct GLFWwindow;
class GameObject;

/*!
\class  PauseSystem
\brief
        System for managing pausing
*/
class PauseSystem : public ISystem{
	public:

		/*!
		\fn     static PauseSystem *getInstance()
		\par    This function has no parameters.
		\return Singleton instance of the pause system
		\brief
		        This function accesses the Singleton instance of the pause system, instantiating it if necessary.
		*/
		static PauseSystem *getInstance();

		/*!
		\fn     static void closeInstance()
		\par    This function has no parameters.
		\brief  See ISystem.h
		*/
		static void closeInstance();

		/*!
		\fn     void initialize()
		\brief  See ISystem.h
		*/
		void initialize() override;

		/*!
		\fn     void update(float &dt)
		\param  dt
		          dt
		\brief  See ISystem.h
		*/
		void update(float &dt) override;

		/*!
		\fn     void shutdown()
		\brief  See ISystem.h
		*/
		void shutdown() override;

		/*!
		\fn     void pause(bool state)
		\param  state
		          If the pause system should be activated
		\return Nothing
		\brief
		        This function activates or deactivates the pause system.
		*/
		void pause(bool state);

		/*!
		\fn     void pause()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function toggles the pause system.
		*/
		void pause();

		/*!
		\fn     void pauseFull()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function attempts to activate the full pause menu.
		*/
		void pauseFull();

		/*!
		\fn     void unpauseLite()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function deactivates the lite pause screen.
		*/
		void unpauseLite();

		/*!
		\fn     bool isPaused()
		\par    This function has no parameters.
		\return If the system is active
		\brief
		        This function accesses the state of the pause system.
		*/
		bool isPaused();

		/*!
		\fn     float getDt()
		\par    This function has no parameters.
		\return Time since previous frame, regardless of pause state
		\brief
		        This function accesses the original (i.e. before pausing) time since the previous frame.
		*/
		float getDt();

		/*!
		\fn     friend void focusPause(GLFWwindow *handle, int isFocused)
		\param  handle
		          Window handle
		\param  isFocused
		          If the window is gaining focus
		\return Nothing
		\brief
		        This function opens and closes the pause menu when the focus status of the window is changed.
		*/
		friend void focusPause(GLFWwindow *handle, int isFocused);

	private:

		/*!
		\var    paused
		          If the game is paused
		*/
		bool paused;

		/*!
		\var    blocked
		          Status level for blocking the system
		*/
		bool blocked;

		/*!
		\var    trueDt
		          Time since previous frame, saved in case of unpausable pop ups
		*/
		float trueDt;

		/*
		\var    popup
		          Pause pop-up object in use
		\var    backup
		          Pop-up object to use, in case the pause menu is not active
		*/
		GameObject *popup, *backup;

		/*!
		\var    instance
		          Singleton instance of the system
		*/
		static PauseSystem *instance;

		/*!
		\fn     PauseSystem()
		\par    This function has no parameters.
		\return Newly constructed pause system
		\brief
		        This function constructs a new pause system.
		*/
		PauseSystem();

};