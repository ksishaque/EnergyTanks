/*!
\file   BehaviorDisplayMultiMonitor.h
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for managing the behavior of a monitor count signifier
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

#include <glm/glm.hpp>

#include "Behavior.h"

class BehaviorDisplayMultiMonitor : public Behavior{
	public:

		/*!
		\fn     BehaviorDisplayMultiMonitor()
		\par    This function has no parameters.
		\return Constructed monitor signifier behavior
		\brief
		        This function constructs a new behavior for an signifier.
		*/
		BehaviorDisplayMultiMonitor();

		/*!
		\fn     BehaviorDisplayMultiMonitor(const BehaviorDisplayMultiMonitor &source)
		\param  source
		          Icon behavior to copy
		\return Constructed monitor signifier behavior
		\brief
		        This function constructs a new signifier behavior by copying an existing signifier behavior.
		*/
		BehaviorDisplayMultiMonitor(const BehaviorDisplayMultiMonitor &source);

		/*!
		\fn     BehaviorDisplayMultiMonitor *clone() const
		\brief  See Component.h
		*/
		BehaviorDisplayMultiMonitor *clone() const override;

		/*!
		\fn     void update(float dt)
		\param  dt
		          dt
		\brief  See Component.h
		*/
		void update(float dt) override;

		/*!
		\fn     void setMultiColor(const glm::vec4 &color)
		\param  color
		          Color to set
		\return Nothing
		\brief
		        This function mutates the color to set when multiple monitors are present.
		*/
		void setMultiColor(const glm::vec4 &color);

		/*!
		\fn     void setSingleColor(const glm::vec4 &color)
		\param  color
		          Color to set
		\return Nothing
		\brief
		        This function mutates the color to set when only a single monitor is present.
		*/
		void setSingleColor(const glm::vec4 &color);
        
	private:

		/*!
		\var    multiColor
		          Color to display when multiple monitors are present
		\var    singleColor
		          Color to display when only a single monitor is present
		*/
		glm::vec4 multiColor, singleColor;

};
