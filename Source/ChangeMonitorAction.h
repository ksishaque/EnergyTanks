/*!
\file   ChangeMonitorAction.h
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for creating and managing an action node for changing monitors
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class ChangeMonitorAction;

#include <string>

#include "ActionNode.h"

#define monitorChange(inc) new ChangeMonitorAction(inc)

/*!
\class  ChangeMonitorAction
\brief
        Nodes in an action list that changes the monitor
*/
class ChangeMonitorAction : public ActionNode{
	public:

		/*!
		\fn     ChangeMonitorAction(int increment)
		\param  int increment
		          Number of monitors to increment by
		\return Newly constructed monitor changing action
		\brief
		        This function constructs a new monitor node.
		*/
		ChangeMonitorAction(int increment);

		/*!
		\fn     void operator()(GameObject *object, float dt)
		\param  object
		          object
		\param  dt
		          dt
		\brief  See ActionNode.h
		*/
		void operator()(GameObject *object, float dt);

		/*!
		\fn     ChangeMonitorAction *clone() const
		\brief  See ActionNode.h
		*/
		ChangeMonitorAction *clone() const;

	private:

		/*!
		\var    increment
		          Number of monitors to increment by
		*/
		int increment;

};