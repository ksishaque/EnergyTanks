/*!
\file   Behavior.h
\author Kevin Shin
\date   10-4-2022
\brief
        Functions for managing a behavior
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once

class Behavior;

#include "Component.h"
#include "Physics.h"
#include "Transform.h"

class Behavior : public Component{
	public:

		/*!
		\fn     Behavior()
		\par    This function takes no parameters.
		\return Constructed behavior
		\brief
		        This function constructs a new behavior.
		*/
		Behavior();

		/*!
		\fn     Behavior(const Behavior &source)
		\param  source
		          Behavior to copy
		\return Constructed behavior
		\brief
		        This function constructs a new behavior.
		*/
		Behavior(const Behavior &source);

		/*!
		\fn     void setPhysics(Physics *physics)
		\param  physics
		          Physics to set as `this -> physics`
		\return Nothing
		\brief
		        This function mutates the physics pointer in the behavior.
		*/
		void setPhysics(Physics *physics);

		/*!
		\fn     Physics *getPhysics()
		\par    This function takes no parameters.
		\return Physics of the game object
		\brief
		        This function accesses the physics pointer in the behavior.
		*/
        Physics *getPhysics();

	private:

		/*!
		\var    physics
		          Physics component of the parent game object, stored for convenience
		*/
		Physics *physics;
};
