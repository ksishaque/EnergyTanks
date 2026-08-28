/*!
\file   ActivateButtonAction.cpp
\author Kevin Shin
\date   4-6-2023
\brief
        Functions for creating and managing an action node for activating a button
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "BehaviorButton.h"
#include "GameObject.h"
#include "ObjectManager.h"

#include "ActivateButtonAction.h"

/*!
\fn     ActivateButtonAction::ActivateButtonAction(const std::string &name)
\param  name
          name
\brief  See ActivateButtonAction.h
*/
ActivateButtonAction::ActivateButtonAction(const std::string &name) : name(name){}

/*!
\fn     void ActivateButtonAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void ActivateButtonAction::operator()(GameObject *obj, float dt){

	//	Check `obj`
	if(!obj){

		ActionNode::operator()(obj, dt);

		return;

	}

	//	Variable: Container to search
	ObjectContainer *man = obj -> getManager();

	//	Check `man`
	if(man == nullptr) man = ObjectManager::getInstance();

	//	Variable: Button object to activate
	GameObject *button = man -> findObject(name);

	//	Check `button`
	if(button){

		//	Variable: Buttom behavior to activate
		BehaviorButton *bhv = dynamic_cast<BehaviorButton *>(button -> get(ComponentTypeEnum::cBehavior));

		//	Open `bhv`
		if(bhv) bhv -> activate(obj -> getTeam());

	}

	//	Recursive call to next
	ActionNode::operator()(obj, dt);

}

/*!
\fn     ActivateButtonAction *ActivateButtonAction::clone() const
\brief  See ActinNode.h
*/
ActivateButtonAction *ActivateButtonAction::clone() const{

	//	Variable: return value / clone of `this`
	ActivateButtonAction *ans = new ActivateButtonAction(name);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}