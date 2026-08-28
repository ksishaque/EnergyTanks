/*!
\file   BehaviorDisplayFullscreen.h
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for managing the behavior of a display mode signifier
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

#include <glm/glm.hpp>

#include "Behavior.h"

class BehaviorDisplayFullscreen : public Behavior{
	public:

		/*!
		\fn     BehaviorDisplayFullscreen()
		\par    This function has no parameters.
		\return Constructed display signifier behavior
		\brief
		        This function constructs a new behavior for an signifier.
		*/
		BehaviorDisplayFullscreen();

		/*!
		\fn     BehaviorDisplayFullscreen(const BehaviorDisplayFullscreen &source)
		\param  source
		          Icon behavior to copy
		\return Constructed display signifier behavior
		\brief
		        This function constructs a new signifier behavior by copying an existing signifier behavior.
		*/
		BehaviorDisplayFullscreen(const BehaviorDisplayFullscreen &source);

		/*!
		\fn     BehaviorDisplayFullscreen *clone() const
		\brief  See Component.h
		*/
		BehaviorDisplayFullscreen *clone() const override;

		/*!
		\fn     void update(float dt)
		\param  dt
		          dt
		\brief  See Component.h
		*/
		void update(float dt) override;

		/*!
		\fn     void setFullscreenColor(const glm::vec4 &color)
		\param  color
		          Color to set
		\return Nothing
		\brief
		        This function mutates the color to set in full screen mode.
		*/
		void setFullscreenColor(const glm::vec4 &color);

		/*!
		\fn     void setWindowedColor(const glm::vec4 &color)
		\param  color
		          Color to set
		\return Nothing
		\brief
		        This function mutates the color to set in windowed mode.
		*/
		void setWindowedColor(const glm::vec4 &color);
        
	private:

		/*!
		\var    fullColor
		          Color to display in full screen mode
		\var    winColor
		          Color to display in windowed mode
		*/
		glm::vec4 fullColor, winColor;

};
