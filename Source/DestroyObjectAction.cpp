/*!
\file   DestroyObjectAction.cpp
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for creating and managing an action node for creating objects
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "GameObject.h"
#include "ObjectManager.h"

#include "DestroyObjectAction.h"

/*!
\fn     DestroyObjectAction::DestroyObjectAction(const std::string &obj)
\param  obj
          object
\brief  See DestroyObjectAction.h
*/
DestroyObjectAction::DestroyObjectAction(const std::string &obj) : obj(obj){}

/*!
\fn     void DestroyObjectAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void DestroyObjectAction::operator()(GameObject *obj, float dt){

	//	Variable: Container to add to
	ObjectContainer *man = nullptr;

	//	Get `man`
	if(obj) man = obj -> getManager();
	if(man == nullptr) man = ObjectManager::getInstance();

	//	Variable: Object to destroy
	GameObject *target = man -> findObject(this -> obj);

	//	Destroy `target`
	if(target) target -> setDestroyed();

	//	Recursive call to next
	completed(obj, dt);

}

/*!
\fn     DestroyObjectAction *DestroyObjectAction::clone() const
\brief  See DestroyObjectAction.h
*/
DestroyObjectAction *DestroyObjectAction::clone() const{

	//	Variable: return value / clone of `this`
	DestroyObjectAction *ans = new DestroyObjectAction(obj);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}