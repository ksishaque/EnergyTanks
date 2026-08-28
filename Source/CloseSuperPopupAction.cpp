/*!
\file   CloseSuperPopupAction.cpp
\author Kevin Shin
\date   3-26-2023
\brief
        Functions for creating and managing an action node for closing a pop up
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "BehaviorPopup.h"
#include "GameObject.h"
#include "PopupObjectList.h"

#include "CloseSuperPopupAction.h"

/*!
\fn     CloseSuperPopupAction::CloseSuperPopupAction()
\brief  See CloseSuperPopupAction.h
*/
CloseSuperPopupAction::CloseSuperPopupAction(){}

/*!
\fn     void CloseSuperPopupAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void CloseSuperPopupAction::operator()(GameObject *obj, float dt){

	//	Check `obj`
	if(obj){

		//	Variable: Container to close
		PopupObjectList *man = dynamic_cast<PopupObjectList *>(obj -> getManager());

		//	Check `man`
		if(man){

			//	Variable: Pop up behavior to close
			BehaviorPopup *bhv = man -> getPopup();

			//	Close `bhv`
			if(bhv) bhv -> setToClose();

		}

	}

}

/*!
\fn     CloseSuperPopupAction *CloseSuperPopupAction::clone() const
\brief  See CloseSuperPopupAction.h
*/
CloseSuperPopupAction *CloseSuperPopupAction::clone() const{

	//	Variable: Return value / clone of `this`
	CloseSuperPopupAction *ans = new CloseSuperPopupAction();

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}