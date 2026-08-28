/*!
\file   LingerAction.h
\author Kevin Shin
\date   3-24-2023
\brief
        Functions for creating and managing an action node for lingering for a frame
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class LingerAction;

#include "SequentialAction.h"

#define linger() new LingerAction()

/*!
\class  LingerAction
\brief
        Nodes in an action list that stall a frame
*/
class LingerAction : public SequentialAction{
	public:

		/*!
		\fn     LingerAction()
		\par    This function has no parameters
		\return Newly constructed lingering action
		\brief
		        This function constructs a new lingering node.
		*/
		LingerAction();

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
		\fn     LingerAction *clone() const
		\brief  See ActionNode.h
		*/
		LingerAction *clone() const;

	private:

		/*!
		\var    frameSwitch
		          If a frame has passed
		*/
		bool frameSwitch;

};