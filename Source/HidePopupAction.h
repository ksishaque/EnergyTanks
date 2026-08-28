/*!
\file   HidePopupAction.h
\author Kevin Shin
\date   3-26-2023
\brief
        Functions for creating and managing an action node for hiding a pop up.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class HidePopupAction;

#include "ActionNode.h"

class BehaviorPopup;

/*!
\class  HidePopupAction
\brief
        Nodes in an action list that hides a pop up
*/
class HidePopupAction : public ActionNode{
	public:

		/*!
		\fn     HidePopupAction(BehaviorPopup *popup)
		\param  popup
		          Behavior of pop up to hide
		\return Newly constructed hiding action
		\brief
		        This function constructs a new hide node.
		*/
		HidePopupAction(BehaviorPopup *popup);

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
		\fn     HidePopupAction *clone() const
		\brief  See ActionNode.h
		*/
		HidePopupAction *clone() const;

	private:

		/*!
		\var    popup
		          Behavior of pop up to hide
		*/
		BehaviorPopup *popup;

};