/*!
\file   FullscreenAction.cpp
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for creating and managing an action node for setting full screen
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "Window.h"

#include "FullscreenAction.h"

/*!
\fn     FullscreenAction::FullscreenAction(bool mode)
\param  mode
          mode
\brief  See FullscreenAction.h
*/
FullscreenAction::FullscreenAction(bool mode) : mode(mode){}

/*!
\fn     void FullscreenAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void FullscreenAction::operator()(GameObject *obj, float dt){

	//	Set full screen
	Window::getInstance() -> setFullscreen(mode);

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     FullscreenAction *FullscreenAction::clone() const
\brief  See FullscreenAction.h
*/
FullscreenAction *FullscreenAction::clone() const{

	//	Variable: return value / clone of `this`
	FullscreenAction *ans = new FullscreenAction(mode);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}