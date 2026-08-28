/*!
\file   BlockAction.cpp
\author Kevin Shin
\date   4-10-2023
\brief
        Functions for creating and managing an action node for blocking the program
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include <glfw/glfw3.h>

#include "BlockAction.h"

/*!
\fn     void BlockAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void BlockAction::operator()(GameObject *obj, float dt){

	//	Wait for GLFW event
	glfwWaitEvents();

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     BlockAction *BlockAction::clone() const
\brief  See BlockAction.h
*/
BlockAction *BlockAction::clone() const{

	//	Variable: return value / clone of `this`
	BlockAction *ans = new BlockAction();

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}