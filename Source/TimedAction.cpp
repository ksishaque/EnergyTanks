/*!
\file   TimedAction.cpp
\author Kevin Shin
\date   3-17-2023
\brief
        Functions for creating and managing an action node for maintaining a sublist of action nodes for a specified time.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "ActionList.h"

#include "TimedAction.h"

/*!
\fn     TimedAction::TimedAction(ActionList *sub, float time)
\param  
\brief  See TimedAction.h
*/
TimedAction::TimedAction(ActionList *sub, float time) : subList(sub), time(time){}

/*!
\fn     void TimedAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void TimedAction::operator()(GameObject *obj, float dt){

	//	Update the parent of `subList`
	subList -> setParent(obj);

	//	Update and check `time`
	time -= dt;
	if(time < 0){

		//	Run `subList` for the remaining time
		subList -> update(dt + time);

		//	Set as completed
		completed(obj, -time);

	}

	//	Run `subList` as normal
	else subList -> update(dt);

}

/*!
\fn     TimedAction *TimedAction::clone() const
\brief  See ActionNode.h
*/
TimedAction *TimedAction::clone() const{

	//	Variable: return value / clone of `this`
	TimedAction *ans = new TimedAction(subList -> clone(), time);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}

/*!
\fn     TimedAction::~TimedAction()
\brief  See ActionNode.h
*/
TimedAction::~TimedAction(){
	delete subList;
}