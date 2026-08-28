/*!
\file   ClickerAction.h
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for creating and managing an action node for producing a consistent testing sound effect
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class ClickerAction;

#include "ActionNode.h"

#define clickAct() new ClickerAction()

/*!
\class  ClickerAction
\brief
        Nodes in an action list that clicks
*/
class ClickerAction : public ActionNode{
	public:

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
		\fn     ClickerAction *clone() const
		\brief  See ActionNode.h
		*/
		ClickerAction *clone() const;

	private:

		/*!
		\var    timer
		          Timer for producing clicking effects
		*/
		static float timer;

};