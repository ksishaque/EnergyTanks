/*!
\file   SleepAction.h
\author Kevin Shin
\date   2-28-2023
\brief
        Functions for creating and managing an action node for waiting.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class SleepAction;

#include "SequentialAction.h"

#define sleep(time) new SleepAction(time)

/*!
\class  SleepAction
\brief
        Nodes in an action list that waits for a set amount of time
*/
class SleepAction : public SequentialAction{
	public:

		/*!
		\fn     SleepAction(float time)
		\param  time
		          Duration of waiting action
		\return Newly constructed waiting action
		\brief
		        This function constructs a new waiting node.
		*/
		SleepAction(float time);

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
		\fn     SleepAction *clone() const
		\brief  See ActionNode.h
		*/
		SleepAction *clone() const;

	private:

		/*!
		\var    time
		          Time to wait
		*/
		float time;

};