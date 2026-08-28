/*!
\file   CloseSuperPopupAction.h
\author Kevin Shin
\date   3-26-2023
\brief
        Functions for creating and managing an action node for closing a pop up
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class CloseSuperPopupAction;

#include <string>

#include "ActionNode.h"

#define closeThisPopup() new CloseSuperPopupAction()

/*!
\class  CloseSuperPopupAction
\brief
        Nodes in an action list that close a pop up
*/
class CloseSuperPopupAction : public ActionNode{
	public:

		/*!
		\fn     CloseSuperPopupAction()
		\par    This function has no parameters.
		\return Newly constructed closing action
		\brief
		        This function constructs a new closing node.
		*/
		CloseSuperPopupAction();

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
		\fn     CloseSuperPopupAction *clone() const
		\brief  See ActionNode.h
		*/
		CloseSuperPopupAction *clone() const;

};