/*!
\file   ObjectCuller.h
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   9-13-2022
\brief
        Functions for creating and maintaining an object culler for the object manager
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once

class ObjectCuller;

#include <vector>
#include "ISystem.h"

class ObjectContainer;

class ObjectCuller : public ISystem{
    public:

		/*!
		\fn     ObjectCuller(ObjectContainer *target)
		\param  target
		          Game object manager to cull objects from.
		\return Constructed object culler
		\brief
		        This function constructs an object culler.
		*/
		ObjectCuller(ObjectContainer &target);

		/*!
		\fn     void update(float dt)
		\param  dt
		          dt
		\brief  See ISystem.h
		*/
        void update(float &dt) override;

		/*!
		\fn     void cull() const
		\return Nothing
		\brief
		        This function culls all objects in the culler.
		*/
		void cull() const;

	private:

		/*!
		\var    objects
		          list of game objects in the manager
		*/
		std::vector<GameObject *> &target;
};