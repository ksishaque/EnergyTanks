/*!
\file   OpenPopupAction.cpp
\author Kevin Shin
\date   3-26-2023
\brief
        Functions for creating and managing an action node for opening a pop up
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "BehaviorPopup.h"
#include "GameObject.h"
#include "ObjectContainer.h"
#include "ObjectManager.h"

#include "OpenPopupAction.h"

/*!
\fn     OpenPopupAction::OpenPopupAction(const std::string &name)
\param  name
          name
\brief  See OpenPopupAction.h
*/
OpenPopupAction::OpenPopupAction(const std::string &name) : name(name){}

/*!
\fn     void OpenPopupAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void OpenPopupAction::operator()(GameObject *obj, float dt){

	//	Variable: Container to search
	ObjectContainer *man = nullptr;

	//	Get `man`
	if(obj) man = obj -> getManager();
	if(man == nullptr) man = ObjectManager::getInstance();

	//	Variable: Pop up object to open
	GameObject *popUp = man -> findObject(name);

	//	Check `popUp`
	if(popUp){

		//	Variable: Pop up behavior to open
		BehaviorPopup *bhv = dynamic_cast<BehaviorPopup *>(popUp -> get(ComponentTypeEnum::cBehavior));

		//	Open `bhv`
		if(bhv) bhv -> open();

	}

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     OpenPopupAction *OpenPopupAction::clone() const
\brief  See OpenPopupAction.h
*/
OpenPopupAction *OpenPopupAction::clone() const{

	//	Variable: return value / clone of `this`
	OpenPopupAction *ans = new OpenPopupAction(name);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}