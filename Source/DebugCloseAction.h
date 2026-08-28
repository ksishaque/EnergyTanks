/*!
\file   DebugCloseAction.h
\author Kevin Shin
\date   4-2-2023
\brief
        Functions for creating and managing an action node for closing debug flags
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

#include "Trace.h"
#ifdef DEBUG_SYSTEM

class DebugCloseAction;

#include "DebugSystem.h"

#include "ActionNode.h"

/*!
\class  DebugCloseAction
\brief
        Nodes in an action list that closes a debug flag
*/
class DebugCloseAction : public ActionNode{
	public:

		/*!
		\fn     DebugCloseAction(DebugSystem::DebugFlag flag)
		\param  flag
		          Flag to close
		\return Newly constructed debug closing action
		\brief
		        This function constructs a new debug node.
		*/
		DebugCloseAction(DebugSystem::DebugFlag flag);

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
		\fn     DebugCloseAction *clone() const
		\brief  See ActionNode.h
		*/
		DebugCloseAction *clone() const;

	private:

		/*!
		\var    flag
		          Flag to close
		*/
		DebugSystem::DebugFlag flag;

};
#endif