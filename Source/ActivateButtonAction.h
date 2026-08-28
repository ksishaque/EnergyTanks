/*!
\file   ActivateButtonAction.h
\author Kevin Shin
\date   4-6-2023
\brief
        Functions for creating and managing an action node for activating a button
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class ActivateButtonAction;

#include <string>

#include "ActionNode.h"

#define buttonPressAct(name) new ActivateButtonAction(name)

/*!
\class  ActivateButtonAction
\brief
        Nodes in an action list that activates a button
*/
class ActivateButtonAction : public ActionNode{
	public:

		/*!
		\fn     ActivateButtonAction(const std::string &name)
		\param  name
		          Name of the button object to activate (NOTE: THIS IS NOT THE BUTTON NAME)
		\return Newly constructed button action
		\brief
		        This function constructs a new button node.
		*/
		ActivateButtonAction(const std::string &name);

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
		\fn     ActivateButtonAction *clone() const
		\brief  See ActionNode.h
		*/
		ActivateButtonAction *clone() const;

	private:

		/*!
		\var    name
		          Name of the button object to activate
		*/
		std::string name;
};