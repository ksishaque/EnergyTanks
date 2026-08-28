/*!
\file   RepeatAction.cpp
\author Kevin Shin
\date   3-22-2023
\brief
        Functions for creating and managing an action node for repeating a set of sequential nodes
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "ActionList.h"

#include "RepeatAction.h"

/*!
\fn     RepeatAction::RepeatAction(ActionList *list)
\param  list
          list
\brief  See RepeatAction.h
*/
RepeatAction::RepeatAction(ActionList *list) : list(list), obj(nullptr){

	//	Set the first loop
	operator<<(*(list -> get() -> clone()));
	operator<<(*(new RepeatActionEnd(this)));

}

/*!
\fn     void RepeatAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void RepeatAction::operator()(GameObject *obj, float dt){

	//	Save `obj` in case of a repeat
	this -> obj = obj;

	//	Recursive call to `next`
	ActionNode::operator()(obj, dt);

}

/*!
\fn     RepeatAction *RepeatAction::clone() const
\brief  See RepeatAction.h
*/
RepeatAction *RepeatAction::clone() const{

	//	Variable: return value / clone of `this`
	RepeatAction *ans = new RepeatAction(list -> clone());

	//	Return
	return ans;

}

/*!
\fn     RepeatAction::RepeatActionEnd::RepeatActionEnd(RepeatAction *start)
\param  start
          start
\brief  See RepeatAction.h
*/
RepeatAction::RepeatActionEnd::RepeatActionEnd(RepeatAction *start) : start(start){}

/*!
\fn     void RepeatAction::RepeatActionEnd::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void RepeatAction::RepeatActionEnd::operator()(GameObject *obj, float dt){
	start -> repeat(dt);
}

/*!
\fn     RepeatAction::RepeatActionEnd *RepeatAction::RepeatActionEnd::clone() const
\brief  See RepeatAction.h
*/
RepeatAction::RepeatActionEnd *RepeatAction::RepeatActionEnd::clone() const{
	return nullptr;
}

/*!
\fn     void RepeatAction::repeat(float dt)
\param  obj
          object
\param  dt
          dt
\brief  See RepeatAction.h
*/
void RepeatAction::repeat(float dt){

	//	Clear the current loop
	getNext() -> deleteAll();

	//	Set new loop
	operator<<(*(list -> get() -> clone()));
	operator<<(*(new RepeatActionEnd(this)));

	//	Run overtime
	ActionNode::operator()(obj, dt);

}

/*!
\fn     RepeatAction::~RepeatAction()
\brief  See RepeatAction.h
*/
RepeatAction::~RepeatAction(){
	delete list;
}