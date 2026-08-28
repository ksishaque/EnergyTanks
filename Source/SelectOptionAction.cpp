/*!
\file   SelectOptionAction.cpp
\author Kevin Shin
\date   4-3-2023
\brief
        Functions for creating and managing an action node for selecting options
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "BehaviorOptionSelector.h"
#include "GameObject.h"

#include "SelectOptionAction.h"

/*!
\fn     SelectOptionAction::SelectOptionAction(unsigned op)
\param  op
          option
\brief  See SelectOptionAction.h
*/
SelectOptionAction::SelectOptionAction(unsigned op) : option(op){}

/*!
\fn     void SelectOptionAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void SelectOptionAction::operator()(GameObject *obj, float dt){

	//	Check if `obj` is `NULL`
	if(obj == nullptr){

		//	Recursive call to next
		ActionNode::operator()(obj, dt);

		//	Return
		return;

	}

	//	Variable: Selector behavior of `obj`
	BehaviorOptionSelector *sel = dynamic_cast<BehaviorOptionSelector *>(obj -> get(ComponentTypeEnum::cBehavior));

	//	Select option
	if(sel) sel -> setOption(option);

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     SelectOptionAction *SelectOptionAction::clone() const
\brief  See SelectOptionAction.h
*/
SelectOptionAction *SelectOptionAction::clone() const{

	//	Variable: return value / clone of `this`
	SelectOptionAction *ans = new SelectOptionAction(option);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}