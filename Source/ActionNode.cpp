/*!
\file   ActionNode.cpp
\author Kevin Shin
\date   11-22-2022
\brief
        Functions for creating and maintaining a virtual node in an action list
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include <cstdlib>

#include "ActionNode.h"

/*!
\fn     void ActionNode::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void ActionNode::operator()(GameObject *obj, float dt){
	if(next) next -> operator()(obj, dt);
}

/*!
\fn     ActionNode &ActionNode::operator<<(ActionNode &next)
\param  next
          next
\brief  See ActionNode.h
*/
ActionNode &ActionNode::operator<<(ActionNode &next){

	//	Check for `NULL` case
	if(&next == nullptr) return *this;

	//	Recursive call to next, if necessary
	if(this -> next) this -> next -> operator<<(next);

	//	Set `next`
	else{

		//	Set `next`
		this -> next = &next;

		//	Set `prev`
		next.prev = &(this -> next);

	}

	//	Return
	return *this;
}

/*!
\fn     ActionNode::~ActionNode()
\brief  See ActionNode.h
*/
ActionNode::~ActionNode(){
	if(prev) *prev = next;
	if(next) next -> prev = prev;
}

/*!
\fn     ActionNode *ActionNode::cloneNext() const
\brief  See ActionNode.h
*/
ActionNode *ActionNode::cloneNext() const{

	//	Recursive call to next, if necessary
	if(next) return next -> clone();

	//	Return
	return nullptr;

}

/*!
\fn     ActionNode::ActionNode()
\brief  See ActionNode.h
*/
ActionNode::ActionNode() : prev(nullptr), next(nullptr){}

/*!
\fn     void ActionNode::deleteAll()
\brief  See ActionNode.h
*/
void ActionNode::deleteAll(){

	//	Recursive call to next
	if(next) next -> deleteAll();

	//	Destroy current node without calling the destructor
	delete this;
}

/*!
\fn     ActionNode *ActionNode::getNext() const
\brief  See ActionNode.h
*/
ActionNode *ActionNode::getNext() const{
	return next;
}