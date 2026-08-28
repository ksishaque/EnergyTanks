/*!
\file   FadeAction.h
\author Kevin Shin
\date   2-28-2023
\brief
        Functions for creating and managing an action node for fading an object in or out.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class FadeAction;

#include "SequentialAction.h"

#define fade(from, to, time) new FadeAction(from, to, time)

/*!
\class  FadeAction
\brief
        Nodes in an action list that fades an object in or out
*/
class FadeAction : public SequentialAction{
	public:

		/*!
		\fn     FadeAction(float from, float to, float time)
		\param  from
		          Alpha value to start at
		\param  to
		          Alpha value to end at
		\param  time
		          Duration of fading action
		\return Newly constructed fading action
		\brief
		        This function constructs a new fading node.
		*/
		FadeAction(float from, float to, float time);

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
		\fn     FadeAction *clone() const
		\brief  See ActionNode.h
		*/
		FadeAction *clone() const;

	private:

		/*!
		\var    alpha
		          Alpha value to set
		\var    to
		          Alpha value to reach
		\var    da
		          Change in `alpha` over 1 second
		*/
		float alpha, to, da;

};