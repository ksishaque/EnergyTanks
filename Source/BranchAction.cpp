/*!
\file   BranchAction.cpp
\author Kevin Shin
\date   4-5-2023
\brief
        Functions for creating and managing an action node for |
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "ActionList.h"

#include "BranchAction.h"

/*!
\fn     BranchAction::BranchAction(ActionList *list)
\param  list
          list
\brief  See BranchAction.h
*/
BranchAction::BranchAction(ActionList *list) : list(list){}

/*!
\fn     void BranchAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void BranchAction::operator()(GameObject *obj, float dt){

	//	Run `list`
	list -> update(dt, obj);

	//	Recursive call to `next`
	ActionNode::operator()(obj, dt);

}

/*!
\fn     BranchAction *BranchAction::clone() const
\brief  See BranchAction.h
*/
BranchAction *BranchAction::clone() const{

	//	Variable: return value / clone of `this`
	BranchAction *ans = new BranchAction(list -> clone());

	//	Return
	return ans;

}

/*!
\fn     BranchAction::~BranchAction()
\brief  See BranchAction.h
*/
BranchAction::~BranchAction(){
	delete list;
}