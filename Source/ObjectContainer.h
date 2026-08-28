/*!
\file   ObjectContainer.h
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   3-24-2023
\brief
        Functions for creating and maintaining a game object container
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <queue>
#include <string>

class ObjectContainer;

#include "ISystem.h"

class GameObject;
class ObjectCuller;

class ObjectContainer : public ISystem{
    public:

		/*!
		\fn     ObjectContainer()
		\par    This function has no parameters
		\return Constructed object container
		\brief
		        This function constructs a game object container.
		*/
		ObjectContainer();

		/*!
		\fn     void initialize() override
		\brief  See ISystem.h
		*/
		void initialize() override;

		/*!
		\fn     void update(float dt) override
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
		\fn     void setCuller(const ObjectCuller *culler)
		\param  culler
		          Culler to set
		\return Nothing
		\brief
		        This function sets the culler that the container will use to clean up deleted objects.
		*/
		void setCuller(const ObjectCuller *culler);

		/*!
		\fn     virtual void addObject(GameObject *object)
		\param  object
		          Game object to add to the object container
		\return Nothing
		\brief
		        This function adds an object to the object container
		*/
		virtual void addObject(GameObject *object);

		/*!
		\fn     void addObject(const std::string &name, bool global)
		\param  name
		          Name of game object to load
		\param  global
		          If the game object should be loaded from the global folder
		\return Nothing
		\brief
		        This function loads an object from the gamestate's folder or the global folder and adds it to the object container
		*/
		void addObject(const std::string &name, bool global = false);

		/*!
		\fn     const glm::mat4 &getViewMatrix() const
		\par    This function has no parameters.
		\return Viewing matrix of the object container.
		\brief
		        This function accesses the current viewing matrix of an object container.
		*/
		const glm::mat4 &getViewMatrix() const;

		/*!
		\fn     const std::vector<GameObject *> &getObjectList() const
		\par    This function has no parameters.
		\return Reference to the list of objects in the container
		\brief
		        This function accesses the list of game objects in an object container.
		*/
		const std::vector<GameObject *> &getObjectList() const;

		/*!
		\fn     std::vector<GameObject *> &getObjectList()
		\par    This function has no parameters.
		\return Reference to the list of objects in the container
		\brief
		        This function accesses the list of game objects in an object container.
		*/
		std::vector<GameObject *> &getObjectList();

		/*!
		\fn     GameObject *findObject(const std::string &name)
		\param  name
		          Name of the object to find
		\return Reference to the first object found, or `nullptr` if no matches were found
		\brief
		        This function finds a game object in an object container.
		*/
		GameObject *findObject(const std::string &name);

		/*!
		\fn     const GameObject *findObject(const std::string &name) const
		\param  name
		          Name of the object to find
		\return Reference to the first object found, or `nullptr` if no matches were found
		\brief
		        This function finds a game object in an object container.
		*/
		const GameObject *findObject(const std::string &name) const;

		/*!
		\fn     virtual const std::string &getName() const
		\par    This function has no parameters.
		\return Reference to the name of the current gamestate.
		\brief
		        This function access the name of the current state of an object container.
		*/
		virtual const std::string &getName() const = 0;

	protected:

		/*!
		\var    culler
		          Object culler used to clean up old gamestates
		*/
		const ObjectCuller *culler;

		/*!
		\var    matrix
		          Viewing matrix of the container
		*/
		const glm::mat4 *matrix;

		/*!
		\var    objects
		          List of game objects in the container
		*/
		std::vector<GameObject *> objects;

		/*!
		\var    addQueue
		          List of game objects to add to the container
		*/
		std::queue<GameObject *> addQueue;

};