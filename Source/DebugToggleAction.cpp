/*!
\file   DebugToggleAction.cpp
\author Kevin Shin
\date   4-2-2023
\brief
        Functions for creating and managing an action node for toggling debug flags
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "DebugSystem.h"

#ifdef DEBUG_SYSTEM
#include "DebugToggleAction.h"

/*!
\fn     void DebugToggleAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void DebugToggleAction::operator()(GameObject *obj, float dt){

	//	Toggle debug system
	DebugSystem::getInstance() -> toggleFlag(flag);

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     DebugToggleAction *DebugToggleAction::clone() const
\brief  See ActionNode.h
*/
DebugToggleAction *DebugToggleAction::clone() const{

	//	Variable: return value / clone of `this`
	DebugToggleAction *ans = new DebugToggleAction(flag);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}

/*!
\fn     DebugToggleAction::DebugToggleAction(DebugSystem::DebugFlag flag)
\param  flag
          flag
\brief  See DebugToggleAction.h
*/
DebugToggleAction::DebugToggleAction(DebugSystem::DebugFlag flag) : ActionNode(), flag(flag){}
#endif