/*!
\file   ReloadAction.cpp
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for creating and managing an action node for reloading a set of sequential nodes
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "ActionList.h"

#include "ReloadAction.h"

/*!
\fn     ReloadAction::ReloadAction(ActionList *list)
\param  list
          list
\brief  See ReloadAction.h
*/
ReloadAction::ReloadAction(ActionList *list) : list(list){}

/*!
\fn     void ReloadAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void ReloadAction::operator()(GameObject *obj, float dt){

	//	Variable: Cloned list to run
	ActionList *clone = list -> clone();

	//	Run and delete
	clone -> update(dt, obj);
	delete clone;

	//	Recursive call to `next`
	ActionNode::operator()(obj, dt);

}

/*!
\fn     ReloadAction *ReloadAction::clone() const
\brief  See ReloadAction.h
*/
ReloadAction *ReloadAction::clone() const{

	//	Variable: return value / clone of `this`
	ReloadAction *ans = new ReloadAction(list -> clone());

	//	Return
	return ans;

}

/*!
\fn     ReloadAction::~ReloadAction()
\brief  See ReloadAction.h
*/
ReloadAction::~ReloadAction(){
	delete list;
}