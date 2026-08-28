/*!
\file   BehaviorConfirmIcon.h
\author Kevin Shin
\date   3-22-2023
\brief
        Functions for managing the behavior of an agreement button confirmation icon
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

#include <string>

#include "Behavior.h"

class BehaviorConfirmIcon : public Behavior{
	public:

		/*!
		\fn     BehaviorConfirmIcon()
		\par    This function has no parameters.
		\return Constructed icon behavior
		\brief
		        This function constructs a new behavior for an icon.
		*/
		BehaviorConfirmIcon();

		/*!
		\fn     BehaviorConfirmIcon(const BehaviorConfirmIcon &source)
		\param  source
		          Icon behavior to copy
		\return Constructed icon behavior
		\brief
		        This function constructs a new icon behavior by copying an existing icon behavior.
		*/
		BehaviorConfirmIcon(const BehaviorConfirmIcon &source);

		/*!
		\fn     BehaviorConfirmIcon *clone() const
		\brief  See Component.h
		*/
		BehaviorConfirmIcon *clone() const override;

		/*!
		\fn     void update(float dt)
		\param  dt
		          dt
		\brief  See Component.h
		*/
		void update(float dt) override;

		/*!
		\fn     void setTarget(const std::string &name)
		\param  name
		          Name of button object with the decision to check for
		\return Nothing
		\brief
		        This function mutates what decision the icon should check for.
		*/
		void setTarget(const std::string &name);
        
	private:

		/*!
		\var    init
		          If the sprite's initial color has to be set
		*/
		bool init;

		/*!
		\var    timer
		          Timer for animation
		*/
		float timer;

		/*!
		\var    target
		          Name of the button object with the decision to check for
		*/
		std::string target;

};
