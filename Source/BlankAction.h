/*!
\file   BlankAction.h
\author Kevin Shin
\date   2-28-2023
\brief
        Functions for creating and managing an action node that does nothing
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class BlankAction;

#include <string>

#include "ActionNode.h"

#define blankAct new BlankAction()

/*!
\class  BlankAction
\brief
        Nodes in an action list that does nothing, used to prevent dangling pointers when removing a head
*/
class BlankAction : public ActionNode{
	public:

		/*!
		\fn     BlankAction()
		\par    This function has no paramenters
		\return Newly constructed blank action
		\brief
		        This function constructs a new blank node.
		*/
		BlankAction();

		/*!
		\fn     BlankAction *clone() const
		\brief  See ActionNode.h
		*/
		BlankAction *clone() const;

	private:

};