/*!
\file   BehaviorConfirmIcon.cpp
\author Kevin Shin
\date   3-22-2023
\brief
        Functions for managing the behavior of an agreement button confirmation icon
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "BehaviorButton.h"
#include "GameObject.h"
#include "Sprite.h"
#include "TeamSystem.h"

#include "BehaviorConfirmIcon.h"

/*!
\fn     BehaviorConfirmIcon::BehaviorConfirmIcon()
\brief  See BehaviorConfirmIcon.h
*/
BehaviorConfirmIcon::BehaviorConfirmIcon() : Behavior(), init(true), timer(-1), target(""){}

/*!
\fn     BehaviorConfirmIcon::BehaviorConfirmIcon(const BehaviorConfirmIcon &that)
\param  that
          source
\brief  See BehaviorConfirmIcon.h
*/
BehaviorConfirmIcon::BehaviorConfirmIcon(const BehaviorConfirmIcon &that) : Behavior(), init(true), timer(-1){
	target = "~" + that.target;
}

/*!
\fn     static bool checkConfirm(GameObject::Team team, const std::string &name)
\param  team
          Team to check
\param  name
          Name to look for
\return If the team's decision matches `name`
\brief
*/
static bool checkConfirm(GameObject::Team team, const std::string &name){

	//	Variable: Decision of `team`
	BehaviorButton *dec = TeamSystem::getInstance() -> getDecision(team);

	//	Check `dec`
	if(dec == nullptr) return false;

	//	Check name
	return dec -> checkDecName(name);

}

/*!
\fn     void BehaviorConfirmIcon::update(float dt)
\param  dt
          dt
\brief  See Component.h
*/
void BehaviorConfirmIcon::update(float dt){

	//	Variable: Parent object
	GameObject *obj = getParent();

	//	Check `obj`
	if(obj == nullptr) return;

	//	Variable: Sprite of `obj`
	Sprite *spr = dynamic_cast<Sprite *>(obj -> get(ComponentTypeEnum::cSprite));

	//	Check `spr`
	if(spr == nullptr) return;

	//	Check for initial sprite color
	if(init){

		//	Set color
		spr -> setColor(0, 0, 0, 1);

		//	Deactivate initial setter
		init = false;

	}

	//	Check for deactivated state
	else if(timer < 0){

		//	Check for activation
		if(checkConfirm(obj -> getTeam(), target)){
			
			//	Activate
			timer = 0;

			//	Set color
			spr -> setColor(1, 1, 1, 1);

		}

	}
	else{

		//	Check for deactivation
		if(!checkConfirm(obj -> getTeam(), target)){
			
			//	Activate
			timer = -1;

			//	Set color
			spr -> setColor(0, 0, 0, 1);

		}

		//	Check for animation
		if(timer < 1){

			//	Increment `timer`
			timer += dt;

			//	Set color
			if((bool)(((int)(timer * 4)) % 2)) spr -> setColor(0, 0, 0, 1);
			else spr -> setColor(1, 1, 1, 1);

		}

	}

}

/*!
\fn     BehaviorConfirmIcon *BehaviorConfirmIcon::clone() const
\brief  See Component.h
*/
BehaviorConfirmIcon *BehaviorConfirmIcon::clone() const{
	return new BehaviorConfirmIcon(*this);
}

/*!
\fn     void BehaviorConfirmIcon::setTarget(const std::string &name)
\param  name
          name
\brief  See BehaviorConfirmIcon.h
*/
void BehaviorConfirmIcon::setTarget(const std::string &name){
	target = name;
}