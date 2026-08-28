/*!
\file   BlockAction.h
\author Kevin Shin
\date   4-10-2023
\brief
        Functions for creating and managing an action node for blocking the program
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class BlockAction;

#include "ActionNode.h"

#define blockAct new BlockAction()

/*!
\class  BlockAction
\brief
        Nodes in an action list that blocks the program until there is a GLFW event
*/
class BlockAction : public ActionNode{
	public:

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
		\fn     BlockAction *clone() const
		\brief  See ActionNode.h
		*/
		BlockAction *clone() const;

};