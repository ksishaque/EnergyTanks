/*!
\file   HidePopupAction.cpp
\author Kevin Shin
\date   3-26-2023
\brief
        Functions for creating and managing an action node for hiding a pop up
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "BehaviorPopup.h"

#include "HidePopupAction.h"

/*!
\fn     HidePopupAction::HidePopupAction(BehaviorPopup *b)
\param  b
          popup
\brief  See HidePopupAction.h
*/
HidePopupAction::HidePopupAction(BehaviorPopup *b) : popup(b){}

/*!
\fn     void HidePopupAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void HidePopupAction::operator()(GameObject *obj, float dt){
	popup -> hide();
}

/*!
\fn     HidePopupAction *HidePopupAction::clone() const
\brief  See HidePopupAction.h
*/
HidePopupAction *HidePopupAction::clone() const{
	return new HidePopupAction(popup);
}