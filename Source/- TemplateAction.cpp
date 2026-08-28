/*!
\file   ?Action.cpp
\author Kevin Shin
\date   |-|-2023
\brief
        Functions for creating and managing an action node for |
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "?Action.h"

/*!
\fn     ?Action::?Action(const std::string &name)
\param  
\brief  See ?Action.h
*/
?Action::?Action() : {}

/*!
\fn     void ?Action::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void ?Action::operator()(GameObject *obj, float dt){

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     ?Action *?Action::clone() const
\brief  See ?Action.h
*/
?Action *?Action::clone() const{

	//	Variable: return value / clone of `this`
	?Action *ans = new ?Action(state);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}