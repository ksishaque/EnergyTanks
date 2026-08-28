/*!
\file   TeamColorIncrementAction.h
\author Kevin Shin
\date   3-16-2023
\brief
        Functions for creating and managing an action node for cycling a team color
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class TeamColorIncrementAction;

#include "ActionNode.h"

#define incrementTeamColor(team, ratio) new TeamColorIncrementAction(team, ratio)

/*!
\class  TeamColorIncrementAction
\brief
        Nodes in an action list that increment a team's color
*/
class TeamColorIncrementAction : public ActionNode{
	public:

		/*!
		\fn     TeamColorIncrementAction(int team, float ratio)
		\param  team
		          Team to increment the color of
		\param  ratio
		          `dc`/`dt` ratio, measured in "sixth-wheels per second" (i.e. a ratio of 1 means it will take 1 second for the color to wrap around the color wheel)
		\return Newly constructed team color action
		\brief
		        This function constructs a new team color node.
		*/
		TeamColorIncrementAction(int team, float ratio);

		/*!
		\fn     void operator()(GameObject *object, float dt)
		\param  object
		          object
		\param  dt
		          dt
		\brief  See ActionNode.h
		*/
		void operator()(GameObject *object, float dt);

		/*!
		\fn     TeamColorIncrementAction *clone() const
		\brief  See ActionNode.h
		*/
		TeamColorIncrementAction *clone() const;

	private:

		/*!
		\var    team
		          Team to update
		*/
		int team;

		/*!
		\var    ratio
		          `dc`/`dt` ratio
		*/
		float ratio;

};