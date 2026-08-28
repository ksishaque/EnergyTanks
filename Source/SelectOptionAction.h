/*!
\file   SelectOptionAction.h
\author Kevin Shin
\date   4-3-2023
\brief
        Functions for creating and managing an action node for selecting options
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class SelectOptionAction;

#include "ActionNode.h"

#define selectOption(name) new SelectOptionAction(name)

/*!
\class  SelectOptionAction
\brief
        Nodes in an action list that select a new option in an option track
*/
class SelectOptionAction : public ActionNode{
	public:

		/*!
		\fn     SelectOptionAction(unsigned option)
		\param  option
		          Option to select
		\return Newly constructed selecting action
		\brief
		        This function constructs a new selecting node.
		*/
		SelectOptionAction(unsigned option);

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
		\fn     SelectOptionAction *clone() const
		\brief  See ActionNode.h
		*/
		SelectOptionAction *clone() const;

	private:

		/*!
		\var    option
		          Option to change to
		*/
		unsigned option;

};