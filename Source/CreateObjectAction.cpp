/*!
\file   CreateObjectAction.cpp
\author Kevin Shin
\date   3-16-2023
\brief
        Functions for creating and managing an action node for creating objects
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "GameObject.h"
#include "ObjectManager.h"

#include "CreateObjectAction.h"

/*!
\fn     CreateObjectAction::CreateObjectAction(const std::string &obj, bool g)
\param  obj
          object
\param  g
          global
\brief  See CreateObjectAction.h
*/
CreateObjectAction::CreateObjectAction(const std::string &obj, bool g) : obj(obj), global(g){}

/*!
\fn     void CreateObjectAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void CreateObjectAction::operator()(GameObject *obj, float dt){

	//	Variable: Container to add to
	ObjectContainer *man = nullptr;

	//	Get `man`
	if(obj) man = obj -> getManager();
	if(man == nullptr) man = ObjectManager::getInstance();

	//	Create new object
	man -> addObject(this -> obj, global);

	//	Recursive call to next
	completed(obj, dt);

}

/*!
\fn     CreateObjectAction *CreateObjectAction::clone() const
\brief  See CreateObjectAction.h
*/
CreateObjectAction *CreateObjectAction::clone() const{

	//	Variable: return value / clone of `this`
	CreateObjectAction *ans = new CreateObjectAction(obj, global);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}