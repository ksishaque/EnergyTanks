/*!
\file   ActionList.cpp
\author Kevin Shin
\date   11-22-2022
\brief
        Functions for creating and managing a list of actions
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "ActionNode.h"
#include "PauseSystem.h"

#include "ActionList.h"

/*!
\fn     ActionList::ActionList()
\brief  See ActionList.h
*/
ActionList::ActionList() : Component(ComponentTypeEnum::cActionList), list(nullptr){}

/*!
\fn     ActionList::ActionList(const ActionList &that)
\param  that
          source
\brief  See ActionList.h
*/
ActionList::ActionList(const ActionList &that) : Component(ComponentTypeEnum::cActionList), list(that.list -> clone()){
	list -> prev = &list;
}

/*!
\fn     void ActionList::update(float dt)
\param  dt
          dt
\brief  See Component.h
*/
void ActionList::update(float dt){
	if(list) list -> operator()(getParent(), dt);
}

/*!
\fn     void ActionList::add(ActionNode *node)
\param  node
          node
\brief  See ActionList.h
*/
void ActionList::add(ActionNode *node){

	//	Add to `list` if it is not empty
	if(list) list -> operator<<(*node);

	//	Set as the first node of `list` otherwise
	else{

		//	Set as `list`
		list = node;

		//	Set the `prev` pointer
		node -> prev = &list;

	}

}

/*!
\fn     ActionList::~ActionList()
\brief  See ActionList.h
*/
ActionList::~ActionList(){
	if(list) list -> deleteAll();
}

/*!
\fn     void ActionList::clear()
\brief  See ActionList.h
*/
void ActionList::clear(){

	//	Delete `list`
	if(list){

		//	Delete `list`
		list -> deleteAll();
		list = nullptr;
	}
}

/*!
\fn     ActionList *ActionList::clone() const
\brief  See Component.h
*/
ActionList *ActionList::clone() const{
	return new ActionList(*this);
}

/*!
\fn     ActionNode *ActionList::get()
\brief  See ActionList.h
*/
ActionNode *ActionList::get(){
	return list;
}

/*!
\fn     void ActionList::add(const ActionList *list)
\param  list
          list
\brief  See ActionList.h
*/
void ActionList::add(const ActionList *list){
	if(list) add(list -> get() -> clone());
}

/*!
\fn     const ActionNode *ActionList::get() const
\brief  See ActionList.h
*/
const ActionNode *ActionList::get() const{
	return list;
}

/*!
\fn     void ActionList::update(float dt, GameObject *obj)
\param  dt
          dt
\param  obj
          object
\brief  See ActionList.h
*/
void ActionList::update(float dt, GameObject *obj){
	if(list && obj) list -> operator()(obj, dt);
}