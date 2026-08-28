/*!
\file   ClosePopupAction.cpp
\author Kevin Shin
\date   3-26-2023
\brief
        Functions for creating and managing an action node for closing a pop up
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "BehaviorPopup.h"
#include "GameObject.h"
#include "ObjectContainer.h"
#include "ObjectManager.h"

#include "ClosePopupAction.h"

/*!
\fn     ClosePopupAction::ClosePopupAction(const std::string &name)
\param  name
          name
\brief  See ClosePopupAction.h
*/
ClosePopupAction::ClosePopupAction(const std::string &name) : name(name){}

/*!
\fn     void ClosePopupAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void ClosePopupAction::operator()(GameObject *obj, float dt){

	//	Variable: Container to search
	ObjectContainer *man = nullptr;

	//	Get `man`
	if(obj) man = obj -> getManager();
	if(man == nullptr) man = ObjectManager::getInstance();

	//	Variable: Pop up object to close
	GameObject *popUp = man -> findObject(name);

	//	Check `popUp`
	if(popUp){

		//	Variable: Pop up behavior to close
		BehaviorPopup *bhv = dynamic_cast<BehaviorPopup *>(popUp -> get(ComponentTypeEnum::cBehavior));

		//	Close `bhv`
		if(bhv) bhv -> close();

	}

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     ClosePopupAction *ClosePopupAction::clone() const
\brief  See ClosePopupAction.h
*/
ClosePopupAction *ClosePopupAction::clone() const{

	//	Variable: return value / clone of `this`
	ClosePopupAction *ans = new ClosePopupAction(name);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}