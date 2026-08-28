/*!
\file   ChangeStateAction.cpp
\author Kevin Shin
\date   11-22-2022
\brief
        Functions for creating and managing an action node for changing game states
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "ObjectManager.h"
#include "Trace.h"
#include "SoundSystem.h"
#include "ChangeStateAction.h"

/*!
\fn     ChangeStateAction::ChangeStateAction(const std::string &name)
\param  name
          stateName
\brief  See ChangeStateAction.h
*/
ChangeStateAction::ChangeStateAction(const std::string &name) : ActionNode(), state(name){}

/*!
\fn     void ChangeStateAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void ChangeStateAction::operator()(GameObject *obj, float dt){

	//	Trace message for debug
    //Trace::message("Change State Action: %s", state);

	//	Load new gamestate
	ObjectManager::getInstance() -> changeState(state);

	//	Recursive call to next
	ActionNode::operator()(obj, dt);
}

/*!
\fn     ChangeStateAction *ChangeStateAction::clone() const
\brief  See ChangeStateAction.h
*/
ChangeStateAction *ChangeStateAction::clone() const{

	//	Variable: return value / clone of `this`
	ChangeStateAction *ans = new ChangeStateAction(state);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;
}