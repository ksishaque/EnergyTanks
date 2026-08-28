/*!
\file   FlickerAction.h
\author Kevin Shin
\date   |-|-2023
\brief
        Functions for creating and managing an action node for flickering effects
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class FlickerAction;

#include <string>

#include "ActionNode.h"

#define flicker(chance) new FlickerAction(chance)

/*!
\class  FlickerAction
\brief
        Nodes in an action list that cause the object to flicker randomly
*/
class FlickerAction : public ActionNode{
	public:

		/*!
		\fn     FlickerAction(int chance)
		\param  chance
		          Chance of flickering this frame
		\return Newly constructed flicker action
		\brief
		        This function constructs a new flicker node.
		*/
		FlickerAction(int chance);

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
		\fn     FlickerAction *clone() const
		\brief  See ActionNode.h
		*/
		FlickerAction *clone() const;

	private:

		/*!
		\var    chance
		          Denominator of chance to flicker
		*/
		int chance;

};