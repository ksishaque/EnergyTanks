/*!
\file   TimedAction.h
\author Kevin Shin
\date   3-16-2023
\brief
        Functions for creating and managing an action node for maintaining a sublist of action nodes for a specified time.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class TimedAction;

#include <string>

#include "SequentialAction.h"

#define timedAct(subList, time) new TimedAction(subList, time)

class ActionList;

/*!
\class  TimedAction
\brief
        Nodes in an action list that run a sublist of nodes for a given time
*/
class TimedAction : public SequentialAction{
	public:

		/*!
		\fn     TimedAction(ActionList *subList, float time)
		\param  subList
		          Action node(s) to run for the alotted time
		\param  time
		          Time to run for
		\return Newly constructed timed action
		\brief
		        This function constructs a new timed node.
		*/
		TimedAction(ActionList *subList, float time);

		/*!
		\fn     ~TimedAction()
		\brief  See ActionNode.h
		*/
		~TimedAction();

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
		\fn     TimedAction *clone() const
		\brief  See ActionNode.h
		*/
		TimedAction *clone() const;

	private:

		/*!
		\var    time
		          Remaining duration of the action
		*/
		float time;

		/*!
		\var    subList
		*/
		ActionList *subList;

};