/*!
\file   OpenPopupAction.h
\author Kevin Shin
\date   3-26-2023
\brief
        Functions for creating and managing an action node for opening a pop up
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class OpenPopupAction;

#include <string>

#include "ActionNode.h"

#define openPopup(name) new OpenPopupAction(name)

/*!
\class  OpenPopupAction
\brief
        Nodes in an action list that open a pop up
*/
class OpenPopupAction : public ActionNode{
	public:

		/*!
		\fn     OpenPopupAction(const std::string &name)
		\param  name
		          Name of the pop up object to open
		\return Newly constructed opening action
		\brief
		        This function constructs a new opening node.
		*/
		OpenPopupAction(const std::string &name);

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
		\fn     OpenPopupAction *clone() const
		\brief  See ActionNode.h
		*/
		OpenPopupAction *clone() const;

	private:

		/*!
		\var    name
		          Name of the pop up object to open
		*/
		std::string name;

};