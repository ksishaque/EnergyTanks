/*!
\file   CheckTeamLossCondition.h
\author Kevin Shin
\date   11-22-2022
\brief
        Functions for creating and managing a conditional node for checking if a team has lost
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

class CheckTeamLossCondition;

#include "ConditionNode.h"
#include "GameObject.h"

#define checkTeamLoss(team) new CheckTeamLossCondition(team)

/*!
\class  CheckTeamLossCondition
\brief
        Action nodes that only continues in the list when the designated team has lost
*/
class CheckTeamLossCondition : public ConditionNode{
	public:

		/*!
		\fn     CheckTeamLossCondition(GameObject::Team team)
		\param  team
		          Team to check
		\return Newly constructed teamloss condition
		\brief
		        This function constructs a new teamloss node.
		*/
		CheckTeamLossCondition(GameObject::Team team);

		/*!
		\fn     CheckTeamLossCondition *clone() const
		\brief  See ConditionNode.h
		*/
		CheckTeamLossCondition *clone() const;

	private:

		/*!
		\fn     bool condition()
		\brief  See ConditionNode.h
		*/
		bool condition();

		/*!
		\var    team
		          Team to check
		*/
		GameObject::Team team;
};