/*!
\file   LingerAction.cpp
\author Kevin Shin
\date   3-24-2023
\brief
        Functions for creating and managing an action node for lingering for a frame
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "LingerAction.h"

/*!
\fn     LingerAction::LingerAction()
\brief  See LingerAction.h
*/
LingerAction::LingerAction() : frameSwitch(false){}

/*!
\fn     void LingerAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void LingerAction::operator()(GameObject *obj, float dt){

	//	Check `frameSwitch`
	if(frameSwitch) completed(obj, dt);
	else frameSwitch = true;

}

/*!
\fn     LingerAction *LingerAction::clone() const
\brief  See LingerAction.h
*/
LingerAction *LingerAction::clone() const{

	//	Variable: return value / clone of `this`
	LingerAction *ans = new LingerAction();

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}