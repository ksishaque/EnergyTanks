/*!
\file   BehaviorTeamButton.h
\author Kevin Shin
\date   3-26-2023
\brief
        Functions for managing the behavior of a team specific button
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

#include <string>

#include "BehaviorButton.h"

class BehaviorTeamButton : public BehaviorButton{
	public:

		/*!
		\fn     BehaviorTeamButton()
		\par    This function has no parameters.
		\return Constructed icon behavior
		\brief
		        This function constructs a new behavior for an icon.
		*/
		BehaviorTeamButton();

		/*!
		\fn     BehaviorTeamButton(const BehaviorTeamButton &source)
		\param  source
		          Icon behavior to copy
		\return Constructed icon behavior
		\brief
		        This function constructs a new icon behavior by copying an existing icon behavior.
		*/
		BehaviorTeamButton(const BehaviorTeamButton &source);

		/*!
		\fn     BehaviorTeamButton *clone() const override
		\brief  See Component.h
		*/
		BehaviorTeamButton *clone() const override;

		/*!
		\fn     void update(float dt) override
		\param  dt
		          dt
		\brief  See Component.h
		*/
		void update(float dt) override;

		/*!
		\fn     void setParent(GameObject *parent) override
		\param  parent
		          parent
		\brief  See Component.h
		*/
		void setParent(GameObject *parent) override;

		/*!
		\fn     void activate(GameObject::Team team) override
		\param  team
		          team
		\brief  See BehaviorButton.h
		*/
		void activate(GameObject::Team team) override;
        
	private:

		/*!
		\var    team
		          Team of the parent, for convenience
		*/
		GameObject::Team team;

};
