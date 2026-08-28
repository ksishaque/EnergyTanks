/*!
\file   ConditionNode.cpp
\author Kevin Shin
\date   11-24-2022
\brief
        Functions for creating and maintaining a virtual conditional node
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "ConditionNode.h"

/*!
\fn     void ConditionNode::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void ConditionNode::operator()(GameObject *obj, float dt){
	if(condition()) return ActionNode::operator()(obj, dt);
}