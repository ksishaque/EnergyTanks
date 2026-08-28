/*!
\file   Engine.h
\author Kevin Shin
\date   9-13-2022
\brief
		Functions for setting up and running an engine
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once
#include "ISystem.h"
#include <vector>
#include <stack>

/*!
\class  Engine
\par    Base class: 'ISystem'
\brief
		This class stores multiple other 'ISystem's and controls them simultaneously within a main engine loop.
*/
class Engine : public ISystem {
	public:

		/*!
		\fn     Engine()
		\par    This function has no parameters
		\return Constructed engine
		\brief
		        This function constructs an engine.
		*/
		Engine();
	
		/*!
		\fn     void initialize() override
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function initializes the engine, sets the shutdown stack and all of the systems inside it.
		\par    NOTE: THIS FUNCTION INITIALIZES SYSTEMS IN THE ORDER THEY WERE ADDED!
		*/
		void initialize() override;

		/*!
		\fn     void update(float dt) override
		\param  dt
		          time since previous frame
		\return Nothing
		\brief
		        This function updates the engine and all of the systems inside it.
		*/
		void update(float &dt) override;
		
		/*!
		\fn     void shutdown() override
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function shuts down the engine and all of the systems inside it.
		*/
		void shutdown() override;
	
		/*!
		\fn     void addSystem(ISystem *system)
		\param  system:
				  'ISystem' to add to the engine
		\return Nothing
		\brief
				This function adds 'system' to the engine.
		*/
		void addSystem(ISystem* system);
	
		/*!
		\fn     void addSystem(ISystem *system)
		\param  system:
				  'ISystem' to add to the engine
		\return Nothing
		\brief
				This function adds 'system' to the engine.
		*/
		ISystem *get(ISystem::Type type);

        /*!
        \fn     void stop()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function stops the engine from running.
        */
        void stop();

        /*!
        \fn     static Engine *getInstance()
        \return Singleton instance of the engine
        \brief
                This function accesses the singleton instance of the engine, creating it if needed.
        */
        static Engine *getInstance();

		/*!
		\fn     static void closeInstance()
		\return Nothing
		\brief
		        This function closes the singleton instance of the engine.
		*/
		static void closeInstance();

	private:

		/*!
		\var    systems
		          list of systems to run
		*/
		std::vector<ISystem *> systems;

		/*!
		\var    isRunning
		          if the engine is running
		*/
		bool isRunning;

        /*!
        \var    instance
                  singletone instance of engine
        */
        static Engine *instance;

		/*!
		\var    shutdownStack
		          stack dictating the order by which the systems must be shutdown.
		*/
		std::stack<ISystem *> shutdownStack;
};