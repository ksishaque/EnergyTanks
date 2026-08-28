/*!
\file   ChangeStateAction.h
\author Kevin Shin
\date   11-22-2022
\brief
        Functions for creating and managing an action node for changing game states
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

class ChangeStateAction;

#include <string>

#include "ActionNode.h"

#define changeGamestate(name) new ChangeStateAction(name)

/*!
\class  ChangeStateAction
\brief
        Nodes in an action list that changes the gamestate
*/
class ChangeStateAction : public ActionNode{
	public:

		/*!
		\fn     ChangeStateAction(const std::string &stateName)
		\param  stateName
		          name of state to 
		\return Newly constructed changestate action
		\brief
		        This function constructs a new changestate node.
		*/
		ChangeStateAction(const std::string &stateName);

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
		\fn     ChangeStateAction *clone() const
		\brief  See ActionNode.h
		*/
		ChangeStateAction *clone() const;

	private:

		/*!
		\var    state
		          State to switch to
		*/
		std::string state;
};