/*!
\file   ClosePopupAction.h
\author Kevin Shin
\date   3-26-2023
\brief
        Functions for creating and managing an action node for closing a pop up
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class ClosePopupAction;

#include <string>

#include "ActionNode.h"

#define closePopup(name) new ClosePopupAction(name)

/*!
\class  ClosePopupAction
\brief
        Nodes in an action list that close a pop up
*/
class ClosePopupAction : public ActionNode{
	public:

		/*!
		\fn     ClosePopupAction(const std::string &name)
		\param  name
		          Name of the pop up object to close
		\return Newly constructed closing action
		\brief
		        This function constructs a new closing node.
		*/
		ClosePopupAction(const std::string &name);

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
		\fn     ClosePopupAction *clone() const
		\brief  See ActionNode.h
		*/
		ClosePopupAction *clone() const;

	private:

		/*!
		\var    name
		          Name of the pop up object to close
		*/
		std::string name;

};