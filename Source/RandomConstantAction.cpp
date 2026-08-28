/*!
\file   RandomConstantAction.cpp
\author Kevin Shin
\date   4-12-2023
\brief
        Functions for creating and managing an action node for running the same random action every time
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "ActionList.h"
#include "General.h"

#include "RandomConstantAction.h"

/*!
\fn     RandomConstantAction::RandomConstantAction()
\brief  See RandomConstantAction.h
*/
RandomConstantAction::RandomConstantAction() : probability(0), action(nullptr){}

/*!
\fn     void RandomConstantAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void RandomConstantAction::operator()(GameObject *obj, float dt){

	//	Run `action`
	action -> update(dt, obj);

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     RandomConstantAction *RandomConstantAction::clone() const
\brief  See ActionNode.h
*/
RandomConstantAction *RandomConstantAction::clone() const{

	//	Variable: return value / clone of `this`
	RandomConstantAction *ans = new RandomConstantAction(action, probability);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}

/*!
\fn     RandomConstantAction::RandomConstantAction(ActionList *list, unsigned prob)
\param  list
          list
\param  prob
          probability
\brief  See RandomConstantAction.h
*/
RandomConstantAction::RandomConstantAction(ActionList *list, unsigned prob) : probability(prob), action(list){}

/*!
\fn     void RandomConstantAction::addPossibility(ActionList *list)
\param  list
          possibility
\brief  See RandomConstantAction.h
*/
void RandomConstantAction::addPossibility(ActionList *list){

	//	Increment probability
	probability += 1;

	//	Check if `list` replaces `action`
	if(randomInteger(probability) == 0){

		//	Clean up `action`
		delete action;

		//	Add `list`
		action = list;

	}

	//	Clean up `list`
	else delete list;

}

/*!
\fn     RandomConstantAction::~RandomConstantAction()
\brief  See RandomConstantAction.h
*/
RandomConstantAction::~RandomConstantAction(){
	delete action;
}