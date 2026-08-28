/*!
\file   ChangeMonitorAction.cpp
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for creating and managing an action node for changing monitors
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "Window.h"

#include "ChangeMonitorAction.h"

/*!
\fn     ChangeMonitorAction::ChangeMonitorAction(int inc)
\param  inc
          increment
\brief  See ChangeMonitorAction.h
*/
ChangeMonitorAction::ChangeMonitorAction(int inc) : increment(inc){}

/*!
\fn     void ChangeMonitorAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void ChangeMonitorAction::operator()(GameObject *obj, float dt){

	//	Increment monitor
	Window::getInstance() -> changeMonitor(increment);

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     ChangeMonitorAction *ChangeMonitorAction::clone() const
\brief  See ChangeMonitorAction.h
*/
ChangeMonitorAction *ChangeMonitorAction::clone() const{

	//	Variable: return value / clone of `this`
	ChangeMonitorAction *ans = new ChangeMonitorAction(increment);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}