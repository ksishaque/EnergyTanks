/*!
\file   BehaviorDisplayFloatBar.cpp
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for managing the behavior of a monitor count signifier
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "ColorWheel.h"
#include "GameObject.h"
#include "SoundSystem.h"
#include "TeamSystem.h"

#include "BehaviorDisplayFloatBar.h"

/*!
\fn     BehaviorDisplayFloatBar::BehaviorDisplayFloatBar()
\brief  See BehaviorDisplayFloatBar.h
*/
BehaviorDisplayFloatBar::BehaviorDisplayFloatBar() : Behavior(), type(FloatType::INVALID), center(0, 0, 1), range(0){}

/*!
\fn     BehaviorDisplayFloatBar::BehaviorDisplayFloatBar(const BehaviorDisplayFloatBar &that)
\param  that
          source
\brief  See BehaviorDisplayFloatBar.h
*/
BehaviorDisplayFloatBar::BehaviorDisplayFloatBar(const BehaviorDisplayFloatBar &that) : Behavior(), type(that.type), center(that.center), range(that.range){}

/*!
\fn     void BehaviorDisplayFloatBar::update(float dt)
\param  dt
          dt
\brief  See Component.h
*/
void BehaviorDisplayFloatBar::update(float dt){

	//	Variable: Parent object
	GameObject *obj = getParent();

	//	Check `obj`
	if(obj == nullptr) return;

	//	Variable: Transform of `obj`
	Transform *trans = dynamic_cast<Transform *>(obj -> get(ComponentTypeEnum::cTransform));

	//	Check `trans`
	if(trans == nullptr) return;

	//	Variable: Float to display
	float val = -0.5f;

	//	Get `val`
	switch(type){
		case FloatType::MUSIC:
			val += SoundSystem::getInstance() -> getMusicVolume();
			break;
		case FloatType::SFX:
			val += SoundSystem::getInstance() -> getSfxVolume();
			break;
		case FloatType::TEAM_COLOR:
			val += evaluateColor(TeamSystem::getInstance() -> getColor(obj -> getTeam())) / 6;
	}

	//	Move `trans`
	trans -> setTranslation(center.x + (val * range), center.y, center.z);

}

/*!
\fn     BehaviorDisplayFloatBar *BehaviorDisplayFloatBar::clone() const
\brief  See Component.h
*/
BehaviorDisplayFloatBar *BehaviorDisplayFloatBar::clone() const{
	return new BehaviorDisplayFloatBar(*this);
}

/*!
\fn     void BehaviorDisplayFloatBar::setTranslation(const glm::vec3 &trans)
\param  trans
          trans
\brief  See BehaviorDisplayFloatBar.h
*/
void BehaviorDisplayFloatBar::setTranslation(const glm::vec3 &trans){
	center = trans;
}

/*!
\fn     void BehaviorDisplayFloatBar::setRange(float range)
\param  range
          range
\brief  See BehaviorDisplayFloatBar.h
*/
void BehaviorDisplayFloatBar::setRange(float range){
	this -> range = range;
}

/*!
\fn     void BehaviorDisplayFloatBar::setValue(FloatType type)
\param  type
          type
\brief  See BehaviorDisplayFloatBar.h
*/
void BehaviorDisplayFloatBar::setValue(FloatType type){
	this -> type = type;
}