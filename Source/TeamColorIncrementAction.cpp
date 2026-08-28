/*!
\file   TeamColorIncrementAction.cpp
\author Kevin Shin
\date   3-16-2023
\brief
        Functions for creating and managing an action node for cycling a team color
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "TeamSystem.h"

#include "TeamColorIncrementAction.h"

/*!
\fn     TeamColorIncrementAction::TeamColorIncrementAction(int team, float ratio)
\param  team
          team
\param  ratio
          ratio
\brief  See TeamColorIncrementAction.h
*/
TeamColorIncrementAction::TeamColorIncrementAction(int team, float ratio) : team(team), ratio(ratio){}

/*!
\fn     void TeamColorIncrementAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void TeamColorIncrementAction::operator()(GameObject *obj, float dt){

	//	Increment team color
	TeamSystem::getInstance() -> incColor((GameObject::Team) team, ratio * dt);

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     TeamColorIncrementAction *TeamColorIncrementAction::clone() const
\brief  See TeamColorIncrementAction.h
*/
TeamColorIncrementAction *TeamColorIncrementAction::clone() const{

	//	Variable: return value / clone of `this`
	TeamColorIncrementAction *ans = new TeamColorIncrementAction(team, ratio);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}