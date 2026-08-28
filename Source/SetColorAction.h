/*!
\file   SetColorAction.h
\author Kevin Shin
\date   3-17-2023
\brief
        Functions for creating and managing an action node for setting the color of an object.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class SetColorAction;

#include <string>

#include "SequentialAction.h"

#define setColorAct(r, g, b, a) new SetColorAction(r, g, b, a)

/*!
\class  SetColorAction
\brief
        Nodes in an action list that set the object's color
*/
class SetColorAction : public SequentialAction{
	public:

		/*!
		\fn     SetColorAction(float red, float green, float blue, float alpha)
		\param  red
		          Red value to set
		\param  green
		          Green value to set
		\param  blue
		          Blue value to set
		\param  alpha
		          Alpha value to set
		\return Newly constructed color setting action
		\brief
		        This function constructs a new color node.
		*/
		SetColorAction(float red, float green, float blue, float alpha);

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
		\fn     SetColorAction *clone() const
		\brief  See ActionNode.h
		*/
		SetColorAction *clone() const;

	private:

		/*!
		\var    r
		          Red value to set
		\var    g
		          Green value to set
		\var    b
		          Blue value to set
		\var    a
		          Alpha value to set
		*/
		float r, g, b, a;
};