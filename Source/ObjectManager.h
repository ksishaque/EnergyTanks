/*!
\file   ObjectManager.h
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   9-13-2022
\brief
        Functions for creating and maintaining a game object manager
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once
#include <vector>
#include <queue>
#include <string>

class ObjectManager;

#include "ObjectContainer.h"

class GameObject;
class ObjectCuller;

class ObjectManager : public ObjectContainer{
    public:

		/*!
		\fn     static ObjectManager *getInstance(const std::string &name)
		\param  name
		          Name of the state to initialize with
		\return Singleton instance of the object manager
		\brief
		        This function retrieves the Singleton instance of the object manager.
		*/
		static ObjectManager *getInstance(const std::string &name);

		/*!
		\fn     static ObjectManager *getInstance()
		\par    This function has no parameters.
		\return Singleton instance of the object manager
		\brief
		        This function retrieves the Singleton instance of the object manager.
		*/
		static ObjectManager *getInstance();

		/*!
		\fn     static void closeInstance()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function retrieves the Singleton instance of the object manager.
		*/
		static void closeInstance();

		/*!
		\fn     void initialize() override
		\brief  See ISystem.h
		*/
		void initialize() override;

		/*!
		\fn     void update(float dt)
		\param  dt
		          Time since previous frame
		\return Nothing
		\brief
		        This function updates every object in the object manager, then starts the collision queue.
		*/
		void update(float &dt) override;

		/*!
		\fn     void addForeignObject(GameObject *object)
		\param  object
		          Foreign game object to add to the object manager
		\return Nothing
		\brief
		        This function adds an object to be managed but not owned the manager.
		*/
		void addForeignObject(GameObject *object);

		/*!
		\fn     void removeForeignObject(GameObject *object)
		\param  object
		          Foreign game object to remove from the object manager
		\return Nothing
		\brief
		        This function removes a foreign object in the manager.
		*/
		void removeForeignObject(GameObject *object);

		/*!
		\fn     const std::string &getName() const
		\par    This function has no parameters.
		\return Reference to the name of the current gamestate.
		\brief
		        This function access the name of the current state of an object manager.
		*/
		const std::string &getName() const;

		/*!
		\fn     void lockState(bool lock)
		\param  lock
		          If the state should be locked
		\return Nothing
		\brief
		        This function mutates whether or not the state of the manager is locked.
		*/
		void lockState(bool lock = true);

		/*!
		\fn     void changeState(const std::string &stateName)
		\param  stateName
		          Name of the new state to set
		\return Nothing
		\brief
		        This function updates the current state of an object manager to a new state.
		*/
		void changeState(const std::string &stateName);

		/*!
		\fn     void changeState()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function reloads the current state of an object manager.
		*/
		void changeState();

	private:
		
		/*!
		\var    name
		          Name of the current gamestate
		\var    loadLock
		          If the gamestate needs to be reloaded
		\var    loadReset
		          If the gamestate all existing objects need to be flushed beforehand
		\par    stateLock
		          If the gamestate has been locked
		*/
		std::string name;
		bool loadLock, loadReset, stateLock;

		/*!
		\var    foreigners
		          List of game objects in the manager, but owned by another system
		*/
		std::vector<GameObject *> foreigners;

		/*!
		\var    instance
		          Singleton instance of the object manager
		*/
		static ObjectManager *instance;

		/*!
		\var    DEFAULT_MATRIX
		          Default matrix for object managers
		*/
		static const glm::mat4 DEFAULT_MATRIX;

		/*!
		\fn     ObjectManager(const std::string &name)
		\param  name
		          Name of the current state of the manager
		\return Constructed object manager
		\brief
		        This function constructs a game object manager.
		*/
		ObjectManager(const std::string &name);
};