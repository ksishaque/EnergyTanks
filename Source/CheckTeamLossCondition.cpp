/*!
\file   CheckTeamLossCondition.cpp
\author Kevin Shin
\date   11-22-2022
\brief
        Functions for creating and managing a conditional node for checking if a team has lost
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "TeamSystem.h"
#include "Trace.h"

#include "CheckTeamLossCondition.h"

/*!
\fn     CheckTeamLossCondition::CheckTeamLossCondition(GameObject::Team team)
\param  team
          team
\brief  See CheckTeamLossCondition.h
*/
CheckTeamLossCondition::CheckTeamLossCondition(GameObject::Team team) : team(team){}

/*!
\fn     bool CheckTeamLossCondition::condition()
\brief  See CheckTeamLossCondition.h
*/
bool CheckTeamLossCondition::condition(){

	//	Trace message for debug
    //Trace::message("Check if %s team has lost", team == 1 ? "right" : "left");

	//	Check team
	return TeamSystem::getInstance() -> getPlayer(team) == nullptr;
}

/*!
\fn     CheckTeamLossCondition *CheckTeamLossCondition::clone() const
\brief  See CheckTeamLossCondition.h
*/
CheckTeamLossCondition *CheckTeamLossCondition::clone() const{

	//	Variable: return value / clone of `this`
	CheckTeamLossCondition *ans = new CheckTeamLossCondition(team);;

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;
}
