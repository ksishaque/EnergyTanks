/*!
\file   ActivatePopupAction.cpp
\author Kevin Shin
\date   3-26-2023
\brief
        Functions for creating and managing an action node for activating a pop up
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "BehaviorPopup.h"

#include "ActivatePopupAction.h"

/*!
\fn     ActivatePopupAction::ActivatePopupAction(BehaviorPopup *b)
\param  b
          popup
\brief  See ActivatePopupAction.h
*/
ActivatePopupAction::ActivatePopupAction(BehaviorPopup *b) : popup(b){}

/*!
\fn     void ActivatePopupAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void ActivatePopupAction::operator()(GameObject *obj, float dt){
	popup -> activate();
}

/*!
\fn     ActivatePopupAction *ActivatePopupAction::clone() const
\brief  See ActivatePopupAction.h
*/
ActivatePopupAction *ActivatePopupAction::clone() const{
	return new ActivatePopupAction(popup);
}