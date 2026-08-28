/*!
\file   DebugCloseAction.cpp
\author Kevin Shin
\date   4-2-2023
\brief
        Functions for creating and managing an action node for closing debug flags
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "DebugSystem.h"

#ifdef DEBUG_SYSTEM
#include "DebugCloseAction.h"

/*!
\fn     void DebugCloseAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void DebugCloseAction::operator()(GameObject *obj, float dt){

	//	Close debug system
	DebugSystem::getInstance() -> closeFlag(flag);

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     DebugCloseAction *DebugCloseAction::clone() const
\brief  See ActionNode.h
*/
DebugCloseAction *DebugCloseAction::clone() const{

	//	Variable: return value / clone of `this`
	DebugCloseAction *ans = new DebugCloseAction(flag);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}

/*!
\fn     DebugCloseAction::DebugCloseAction(DebugSystem::DebugFlag flag)
\param  flag
          flag
\brief  See DebugCloseAction.h
*/
DebugCloseAction::DebugCloseAction(DebugSystem::DebugFlag flag) : ActionNode(), flag(flag){}
#endif