/*!
\file   SequentialAction.h
\author Kevin Shin
\date   2-28-2023
\brief
        Functions for creating and managing an action node that complete's itself before moving on
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class SequentialAction;

#include "ActionNode.h"

/*!
\class  SequentialAction
\brief
        Nodes in an action list that complete themselves before moving on
*/
class SequentialAction : public ActionNode{
	public:

		/*!
		\fn     SequentialAction()
		\par    This function has no paramenters
		\return Newly constructed sequentail action
		\brief
		        This function constructs a new sequential node.
		*/
		SequentialAction();

	protected:

		/*!
		\fn     void completed(GameObject *object, float overtime)
		\param  object
		          Game object to pass to the next object
		\param  overtime
		          Spillover time after the current action completed
		\brief  This function removes this action from the node and starts the next action(s) with the remaining time.
		*/
		void completed(GameObject *object, float overtime);

};