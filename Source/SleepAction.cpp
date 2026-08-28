/*!
\file   SleepAction.cpp
\author Kevin Shin
\date   2-28-2023
\brief
        Functions for creating and managing an action node for |
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "SleepAction.h"

/*!
\fn     SleepAction::SleepAction(float from, float to, float t)
\param  from
          from
\param  to
          to
\param  t
          time
\brief  See SleepAction.h
*/
SleepAction::SleepAction(float t) : SequentialAction(), time(-t){}

/*!
\fn     void SleepAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void SleepAction::operator()(GameObject *obj, float dt){

	//	Iterate `alpha`
	time += dt;

	//	Check if `to` has been reached
	if(time >= 0) completed(obj, time);

}

/*!
\fn     SleepAction *SleepAction::clone() const
\brief  See SleepAction.h
*/
SleepAction *SleepAction::clone() const{

	//	Variable: return value / clone of `this`
	SleepAction *ans = new SleepAction(-time);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}