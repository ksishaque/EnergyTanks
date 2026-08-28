/*!
\file   SetObjectAction.h
\author Kevin Shin
\date   2-13-2023
\brief
        Functions for creating and managing an action node for setting a game object for future nodes
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class SetObjectAction;

#include <string>

#include "ActionNode.h"

#define setObjectAct(name) new SetObjectAction(name)

/*!
\class  SetObjectAction
\brief
        Nodes in an action list that sets a game object
*/
class SetObjectAction : public ActionNode{
	public:

		/*!
		\fn     SetObjectAction(const std::string &name)
		\param  name
		          Name of object to find and set
		\return Newly constructed object action
		\brief
		        This function constructs a new object node.
		*/
		SetObjectAction(const std::string &name);

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
		\fn     SetObjectAction *clone() const
		\brief  See ActionNode.h
		*/
		SetObjectAction *clone() const;

	private:

		/*!
		\var    name
		          Name of object to set for future nodes
		*/
		std::string name;
};