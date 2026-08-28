/*!
\file   FullscreenCondition.cpp
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for creating and managing a conditional node for checking the full screen state
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "Window.h"

#include "FullscreenCondition.h"

/*!
\fn     bool FullscreenCondition::condition()
\brief  See ConditionNode.h
*/
bool FullscreenCondition::condition(){
	return Window::getInstance() -> isFullscreen();
}

/*!
\fn     FullscreenCondition *FullscreenCondition::clone() const
\brief  See ActionNode.h
*/
FullscreenCondition *FullscreenCondition::clone() const{

	//	Variable: return value / clone of `this`
	FullscreenCondition *ans = new FullscreenCondition();

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}