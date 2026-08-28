/*!
\file   RandomConstantAction.h
\author Kevin Shin
\date   4-12-2023
\brief
        Functions for creating and managing an action node for running the same random action every time
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class RandomConstantAction;

#include "ActionNode.h"

#define randomAct new RandomConstantAction()

class ActionList;

/*!
\class  RandomConstantAction
\brief
        Nodes in an action list that runs the same random action every time
*/
class RandomConstantAction : public ActionNode{
	public:

		/*!
		\fn     RandomConstantAction()
		\par    This function has no parameters
		\return Newly constructed random action
		\brief
		        This function constructs a new random node.
		*/
		RandomConstantAction();

		/*!
		\fn     RandomConstantAction(ActionList *list, unsigned probability)
		\param  list
		          Action list that was currently selected
		\param  probability
		          Number of action lists selected from
		\return Newly constructed random action
		\brief
		        This function constructs a new random node.
		*/
		RandomConstantAction(ActionList *list, unsigned probability);

		/*!
		\fn     ~RandomConstantAction()
		\par    This function has no parameters
		\return Nothing
		\brief
		        This function deconstructs a random node.
		*/
		~RandomConstantAction();

		/*!
		\fn     void addPossibility(ActionList *possibility)
		\param  possibility
		          Possible action list to run; GETS DELETED
		\return Nothing
		\brief
		        This function adds a possible action list to run.
		*/
		void addPossibility(ActionList *possibility);

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
		\fn     RandomConstantAction *clone() const
		\brief  See ActionNode.h
		*/
		RandomConstantAction *clone() const;

	private:

		/*!
		\var    probability
		          Inverse probability that a new action list replaces `action`
		*/
		unsigned probability;

		/*!
		\var    action
		          Action list to run
		*/
		ActionList *action;

};