/*!
\file   FullscreenAction.h
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for creating and managing an action node for setting full screen
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class FullscreenAction;

#include "ActionNode.h"

#define fullscreenAct(mode) new FullscreenAction(mode)

/*!
\class  FullscreenAction
\brief
        Nodes in an action list that sets full screen mode
*/
class FullscreenAction : public ActionNode{
	public:

		/*!
		\fn     FullscreenAction(bool mode)
		\param  mode
		          If full screen should be set
		\return Newly constructed full screen action
		\brief
		        This function constructs a new fulls node.
		*/
		FullscreenAction(bool mode);

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
		\fn     FullscreenAction *clone() const
		\brief  See ActionNode.h
		*/
		FullscreenAction *clone() const;

	private:

		/*!
		\var    mode
		          If full screen should be set
		*/
		bool mode;

};