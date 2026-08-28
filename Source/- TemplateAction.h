/*!
\file   ?Action.h
\author Kevin Shin
\date   |-|-2023
\brief
        Functions for creating and managing an action node for |
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class ?Action;

#include <string>

#include "ActionNode.h"

#define |(name) new ?Action(name)

/*!
\class  ?Action
\brief
        Nodes in an action list that |
*/
class ?Action : public ActionNode{
	public:

		/*!
		\fn     ?Action()
		\param  
		\return Newly constructed | action
		\brief
		        This function constructs a new | node.
		*/
		?Action();

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
		\fn     ?Action *clone() const
		\brief  See ActionNode.h
		*/
		?Action *clone() const;

	private:

};