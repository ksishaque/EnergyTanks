/*!
\file   ShutdownSystem.h
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   4-7-2023
\brief
        Functions for creating and maintaining a shutdown pop-up system
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

class ShutdownSystem;

#include "ISystem.h"

class GameObject;

/*!
\class  ShutdownSystem
\brief
        System for managing the shutdown popup
*/
class ShutdownSystem : public ISystem{
	public:

		/*!
		\fn     static ShutdownSystem *getInstance()
		\par    This function has no parameters.
		\return Singleton instance of the shutdown system
		\brief
		        This function accesses the Singleton instance of the shutdown system, instantiating it if necessary.
		*/
		static ShutdownSystem *getInstance();

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
		\fn     void shutdown()
		\brief  See ISystem.h
		*/
		void shutdown() override;

		/*!
		\fn     void initiateShutdown()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function initiates the shutdown process by opening the shutdown pop-up.
		*/
		void initiateShutdown();

	private:

		/*
		\var    popup
		          Pop-up object to use
		*/
		GameObject *popup;

		/*!
		\var    instance
		          Singleton instance of the system
		*/
		static ShutdownSystem *instance;

		/*!
		\fn     ShutdownSystem()
		\par    This function has no parameters.
		\return Newly constructed shutdown system
		\brief
		        This function constructs a new shutdown system.
		*/
		ShutdownSystem();

};