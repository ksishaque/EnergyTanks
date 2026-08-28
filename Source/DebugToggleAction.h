/*!
\file   DebugToggleAction.h
\author Kevin Shin
\date   4-2-2023
\brief
        Functions for creating and managing an action node for toggling debug flags
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

#include "Trace.h"
#ifdef DEBUG_SYSTEM

class DebugToggleAction;

#include "DebugSystem.h"

#include "ActionNode.h"

/*!
\class  DebugToggleAction
\brief
        Nodes in an action list that toggles a debug flag
*/
class DebugToggleAction : public ActionNode{
	public:

		/*!
		\fn     DebugToggleAction(DebugSystem::DebugFlag flag)
		\param  flag
		          Flag to toggle
		\return Newly constructed debug toggling action
		\brief
		        This function constructs a new debug node.
		*/
		DebugToggleAction(DebugSystem::DebugFlag flag);

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
		\fn     DebugToggleAction *clone() const
		\brief  See ActionNode.h
		*/
		DebugToggleAction *clone() const;

	private:

		/*!
		\var    flag
		          Flag to toggle
		*/
		DebugSystem::DebugFlag flag;

};
#endif