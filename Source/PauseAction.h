/*!
\file   PauseAction.h
\author Kevin Shin
\date   4-10-2023
\brief
        Functions for creating and managing an action nodes for pausing and unpausing the game
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class PauseAction;

#include <string>

#include "ActionNode.h"

#define pauseAct new PauseAction()
#define unpauseAct new UnpauseAction()

/*!
\class  PauseAction
\brief
        Nodes in an action list that pause the game
*/
class PauseAction : public ActionNode{
	public:

		/*!
		\fn     void operator()(GameObject *object, float dt) override
		\param  object
		          object
		\param  dt
		          dt
		\brief  See ActionNode.h
		*/
		void operator()(GameObject *object, float dt) override;

		/*!
		\fn     PauseAction *clone() const override
		\brief  See ActionNode.h
		*/
		PauseAction *clone() const override;

};

/*!
\class  UnpauseAction
\brief
        Nodes in an action list that unpauses the game
*/
class UnpauseAction : public ActionNode{
	public:

		/*!
		\fn     void operator()(GameObject *object, float dt) override
		\param  object
		          object
		\param  dt
		          dt
		\brief  See ActionNode.h
		*/
		void operator()(GameObject *object, float dt) override;

		/*!
		\fn     UnpauseAction *clone() const override
		\brief  See ActionNode.h
		*/
		UnpauseAction *clone() const override;

};