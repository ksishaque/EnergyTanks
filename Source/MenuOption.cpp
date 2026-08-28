/*!
\file   MenuOption.cpp
\author Kevin Shin
\date   4-2-2023
\brief
        Functions for creating and managing a selection menu option
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "ActionList.h"
#include "BehaviorOptionSelector.h"
#include "GameObject.h"
#include "Transform.h"

#include "MenuOption.h"

/*!
\fn     MenuOption::MenuOption()
\brief  See MenuOption.h
*/
MenuOption::MenuOption() : trans(new Transform()){
	for(unsigned i = 0; i < CONTROL_UNIT_KEY_MAX; i += 1) for(unsigned j = 0; j < 3; j += 1) actions[i][j] = nullptr;
}

/*!
\fn     MenuOption::~MenuOption()
\brief  See MenuOption.h
*/
MenuOption::~MenuOption(){

	//	Delete `actions`
	for(unsigned i = 0; i < CONTROL_UNIT_KEY_MAX; i += 1) for(unsigned j = 0; j < 3; j += 1) delete actions[i][j];

	//	Delete `trans`
	delete trans;

}

/*!
\fn     void MenuOption::setAction(ControlUnit::ControlType i, ControlManager::KeyState j, ActionList *act)
\param  i
          type
\param  j
          keyState
\param  act
          action
\brief  See MenuOption.h
*/
void MenuOption::setAction(ControlUnit::ControlType i, ControlManager::KeyState j, ActionList *act){

	//	Delete current action
	delete actions[i][j];

	//	Set new action
	actions[i][j] = act;

}

/*!
\fn     void MenuOption::setTransform(const glm::vec3 &trans, const glm::vec3 &scale, float rot)
\param  trans
          translation
\param  scale
          scale
\param  rot
          rotation
\brief  See MenuOption.h
*/
void MenuOption::setTransform(const glm::vec3 &trans, const glm::vec3 &scale, float rot){

	//	Set `trans`
	this -> trans -> setTranslation(trans);

	//	Set `scale`
	this -> trans -> setScale(scale);

	//	Set `rot`
	this -> trans -> setRotatePos(rot);

}

/*!
\fn     void MenuOption::placeSelector(GameObject *sel) const
\param  sel
          selector
\brief  See MenuOption.h
*/
void MenuOption::placeSelector(GameObject *sel) const{

	//	Check `sel`
	if(sel == nullptr) return;

	//	Variable: Transformation of `par`
	Transform *trans = dynamic_cast<Transform *>(sel -> get(ComponentTypeEnum::cTransform));

	//	Set `trans`
	if(trans){

		//	Set values
		trans -> setTranslation(this -> trans -> getTranslation());
		trans -> setScale(this -> trans -> getScale());
		trans -> setRotatePos(this -> trans -> getRotation());

	}

}

/*!
\fn     void MenuOption::select(GameObject *obj, ControlUnit::ControlType i, ControlManager::KeyState j, float dt)
\param  obj
          selector
\param  i
          action
\param  j
          keyState
\param  dt
          dt
\brief  See MenuOption.h
*/
void MenuOption::select(GameObject *obj, ControlUnit::ControlType i, ControlManager::KeyState j, float dt){
	if(obj && actions[i][j]) actions[i][j] -> update(dt, obj);
}

/*!
\fn     MenuOption::MenuOption(const MenuOption &that)
\param  that
          source
\brief  See MenuOption.h
*/
MenuOption::MenuOption(const MenuOption &that) : trans(trans){
	for(unsigned i = 0; i < CONTROL_UNIT_KEY_MAX; i += 1) for(unsigned j = 0; j < 3; j += 1) actions[i][j] = that.actions[i][j] -> clone();
}