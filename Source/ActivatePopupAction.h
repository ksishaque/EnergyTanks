/*!
\file   ActivatePopupAction.h
\author Kevin Shin
\date   3-26-2023
\brief
        Functions for creating and managing an action node for activating a pop up.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class ActivatePopupAction;

#include "ActionNode.h"

class BehaviorPopup;

/*!
\class  ActivatePopupAction
\brief
        Nodes in an action list that activates a pop up
*/
class ActivatePopupAction : public ActionNode{
	public:

		/*!
		\fn     ActivatePopupAction(BehaviorPopup *popup)
		\param  popup
		          Behavior of pop up to activate
		\return Newly constructed activation action
		\brief
		        This function constructs a new activate node.
		*/
		ActivatePopupAction(BehaviorPopup *popup);

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
		\fn     ActivatePopupAction *clone() const
		\brief  See ActionNode.h
		*/
		ActivatePopupAction *clone() const;

	private:

		/*!
		\var    popup
		          Behavior of pop up to activate
		*/
		BehaviorPopup *popup;

};