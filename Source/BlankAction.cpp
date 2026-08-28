/*!
\file   BlankAction.cpp
\author Kevin Shin
\date   2-28-2023
\brief
        Functions for creating and managing an action node that does nothing
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "BlankAction.h"

/*!
\fn     BlankAction::BlankAction(const std::string &name)
\brief  See BlankAction.h
*/
BlankAction::BlankAction() : ActionNode(){}

/*!
\fn     BlankAction *BlankAction::clone() const
\brief  See BlankAction.h
*/
BlankAction *BlankAction::clone() const{

	//	Variable: return value / clone of `this`
	BlankAction *ans = new BlankAction();

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}