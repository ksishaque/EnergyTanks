/*!
\fnile  PopupObjectList.cpp
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   3-24-2023
\brief
        Functions for creating and maintaining a game object manager
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "BehaviorPopup.h"
#include "GameObject.h"
#include "ObjectContainer.h"
#include "Transform.h"
#include "Trace.h"

#include "PopupObjectList.h"

using std::vector;
using std::string;

/*!
\fn     void PopupObjectList::addObject(GameObject *object)
\param  obj
          object
\brief  See ObjectContainer.h
*/
void PopupObjectList::addObject(GameObject *obj){

	//	Check if `obj` is `NULL`
	if(obj == nullptr) return;
	
	//	Remove colliders and set to visual
	obj -> remove(ComponentTypeEnum::cCollider);
	obj -> setType(GameObject::Type::Visual);

	//	Add to `addQueue`
	addQueue.push(obj);

}

/*!
\fn     PopupObjectList::PopupObjectList(GameObject *parent, const std::string &name)
\param  parent
          parent
\param  name
          name
\brief  See PopupObjectList.h
*/
PopupObjectList::PopupObjectList(BehaviorPopup *par, bool p) : ObjectContainer(), passive(p), nameMade(false), name(""), parent(par){

	//	Check `par`
	if(par == nullptr)
#ifdef DEBUG_SYSTEM
		if(Trace::error("No parent for %s pop up object list", name)) return;
#else
		assert("Pop-up error!");
#endif

	//	Variable: Pop up object
	GameObject *obj = par -> getParent();

	//	Check `obj`
	if(obj == nullptr)
#ifdef DEBUG_SYSTEM
		if(Trace::error("No parent object for %s pop up object list", name)) return;
#else
		assert("Pop-up error!");
#endif

	//	Variable: Transformation of `parent
	Transform *trans = dynamic_cast<Transform *>(obj -> get(ComponentTypeEnum::cTransform));

	//	Check `trans`
	if(trans == nullptr)
#ifdef DEBUG_SYSTEM
		if(Trace::error("No parent transformation for %s submanager", name)) return;
#else
		assert("Pop-up error!");
#endif

	//	Set `matrix`
	matrix = &(trans -> getMatrix());

	//	First attempt to make name
	makeName();

}

/*!
\fn     const std::string &PopupObjectList::getName() const
\brief  See ObjectContainer.h
*/
const std::string &PopupObjectList::getName() const{

	//	Make `name` if needed
	makeName();

	//	Return
	return name;

}

/*!
\fn     void PopupObjectList::makeName() const
\brief  See PopupObjectList.h
*/
void PopupObjectList::makeName() const{

	//	Check `nameMade` or if `parent` is `NULL`
	if(nameMade || parent == nullptr) return;

	//	Variable: Pop up object
	GameObject *obj = parent -> getParent();

	//	Check `obj`
	if(obj){

		//	Start making `name`
		name = "PopUps/" + obj -> getName();
		nameMade = true;

		//	Check `name`
		if(passive) name += "/Passive";
		else name += "/Active";

	}
}

/*!
\fn     BehaviorPopup *PopupObjectList::getPopup()
\brief  See PopupObjectList.h
*/
BehaviorPopup *PopupObjectList::getPopup(){
	return parent;
}