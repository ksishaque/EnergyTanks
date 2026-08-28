/*!
\file   MonitorCondition.cpp
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for creating and managing a conditional node for checking for multiple monitors
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include <glfw/glfw3.h>

#include "MonitorCondition.h"

/*!
\fn     bool MonitorCondition::condition()
\brief  See ConditionNode.h
*/
bool MonitorCondition::condition(){

	//	Variable: Number of monitors
	int mons;

	//	Find `mons`
	glfwGetMonitors(&mons);

	//	Return
	return mons > 1;

}

/*!
\fn     MonitorCondition *MonitorCondition::clone() const
\brief  See ActionNode.h
*/
MonitorCondition *MonitorCondition::clone() const{

	//	Variable: return value / clone of `this`
	MonitorCondition *ans = new MonitorCondition();

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}