/*!
\file   BehaviorDisplayFloatBar.h
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for managing the behavior of a sliding float display
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

#include <glm/glm.hpp>

#include "Behavior.h"

class BehaviorDisplayFloatBar : public Behavior{
	public:

		/*!
		\enum   FloatType
		          Value to look at
		\var    INVALID
		          Default/invalid
		\var    MUSIC
		          Music volume
		\var    SFX
		          Sound effects volume
		\var    TEAM_COLOR
		          Team color value
		*/
		enum FloatType{INVALID, MUSIC, SFX, TEAM_COLOR};

		/*!
		\fn     BehaviorDisplayFloatBar()
		\par    This function has no parameters.
		\return Constructed slider signifier behavior
		\brief
		        This function constructs a new behavior for an signifier.
		*/
		BehaviorDisplayFloatBar();

		/*!
		\fn     BehaviorDisplayFloatBar(const BehaviorDisplayFloatBar &source)
		\param  source
		          Icon behavior to copy
		\return Constructed slider signifier behavior
		\brief
		        This function constructs a new signifier behavior by copying an existing signifier behavior.
		*/
		BehaviorDisplayFloatBar(const BehaviorDisplayFloatBar &source);

		/*!
		\fn     BehaviorDisplayFloatBar *clone() const
		\brief  See Component.h
		*/
		BehaviorDisplayFloatBar *clone() const override;

		/*!
		\fn     void update(float dt)
		\param  dt
		          dt
		\brief  See Component.h
		*/
		void update(float dt) override;

		/*!
		\fn     void setTranslation(const glm::vec3 &trans)
		\param  trans
		          Translation to set
		\return Nothing
		\brief
		        This function mutates the center translation of the slider.
		*/
		void setTranslation(const glm::vec3 &trans);

		/*!
		\fn     void setRange(float range)
		\param  range
		          Range to set
		\return Nothing
		\brief
		        This function mutates the size of the slider.
		*/
		void setRange(float range);

		/*!
		\fn     void setValue(FloatType type)
		\param  type
		          Value type to look at
		\return Nothing
		\brief
		        This function mutates the target float of the slider.
		*/
		void setValue(FloatType type);
        
	private:

		/*!
		\var    type
		          Value to look at
		*/
		FloatType type;

		/*!
		\var    center
		          Center position of the sliding area
		*/
		glm::vec3 center;

		/*!
		\var    range
		          Range of the sliding area
		*/
		float range;

};
