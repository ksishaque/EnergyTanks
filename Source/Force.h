/*!
\file   Force.h
\author Kevin Shin
\date   3-9-2023
\brief
        Functions for creating and managing a knockback force.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class Force;

#include <glm/glm.hpp>

/*!
\class  Force
\brief
        Diminishing velocity used for knockback forces
*/
class Force{
	public:

		/*!
		\fn     Force(const glm::vec3 &direction, float magnitude, float time)
		\param  direction
		          Normalized vector indicating the direction of the force
		\param  magnitude
		          Initial magnitude of the force
		\param  time
		          Lifetime of the force
		\return Newly constructed force
		\brief
		        This function constructs a new knockback force.
		*/
		Force(const glm::vec3 &direction, float magnitude, float time);

		/*!
		\fn     bool apply(glm::vec3 &translation, float &velocityEffect, float dt)
		\param  translation
		          Translation to apply the force to
		\param  velocityEffect
		          Effect that the velocity has on the translation, which will be depleted by every force
		\param  dt
		          Time since previous frame
		\return If the force has been deleted and should be removed from the container.
		\brief
		        This function applies a force to a translation, diminishes the effect of the velocity and updates the lifetime of the force, deleting it if necessary.
		\par    NOTE: THIS FUNCTION MAY DELETE THE OBJECT!
		*/
		bool apply(glm::vec3 &translation, float &velocityEffect, float dt);


	private:

		/*!
		\var    vel
		          Initial velocity effect of the force
		*/
		glm::vec3 vel;

		/*!
		\var    time
		          Remaining lifespan of the force, between 0 and 1
		*/
		float time;

		/*!
		\var    dtScale
		          Scale at which `time` decreases in comparison to one second
		*/
		float dtScale;

};