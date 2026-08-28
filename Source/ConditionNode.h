/*!
\file   ConditionNode.h
\author Kevin Shin
\date   11-24-2022
\brief
        Functions for creating and maintaining a virtual conditional node
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once

#include "ActionNode.h"

class GameObject;

/*!
\class  ConditionNode
\brief
        Abstract class for conditional action nodes
*/
class ConditionNode : public ActionNode{
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

	protected:

		/*!
		\fn     virtual bool condition()
		\return If the condition is true
		\brief
		        This function checks the condition of the node.
		*/
		virtual bool condition() = 0;

};