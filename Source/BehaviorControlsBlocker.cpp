/*!
\file   BehaviorControlsBlocker.cpp
\author Kevin Shin
\date   4-3-2023
\brief
        Functions for managing the behavior of a player selector
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "BehaviorOptionTrack.h"
#include "GameObject.h"
#include "MenuOption.h"
#include "ObjectContainer.h"

#include "BehaviorControlsBlocker.h"

/*!
\fn     BehaviorControlsBlocker::BehaviorControlsBlocker()
\brief  See BehaviorControlsBlocker.h
*/
BehaviorControlsBlocker::BehaviorControlsBlocker() : BehaviorControllable(), time(1){}

/*!
\fn     BehaviorControlsBlocker::BehaviorControlsBlocker(const BehaviorControlsBlocker &that)
\param  that
          source
\brief  See BehaviorControlsBlocker.h
*/
BehaviorControlsBlocker::BehaviorControlsBlocker(const BehaviorControlsBlocker &that) : BehaviorControllable(), time(that.time){}

/*!
\fn     void BehaviorControlsBlocker::update(float dt)
\param  dt
          dt
\brief  See Component.h
*/
void BehaviorControlsBlocker::update(float dt){

	//	Update `time`
	time -= dt;

	//	Update parent
	BehaviorControllable::update(dt);

	//	Expire if `time` runs out
	if(time <= 0){

		//	Variable: Parent object
		GameObject *par = this -> getParent();

		//	Check and delete `par`
		if(par) par -> setDestroyed();

	}

}

/*!
\fn     BehaviorControlsBlocker *BehaviorControlsBlocker::clone() const
\brief  See Component.h
*/
BehaviorControlsBlocker *BehaviorControlsBlocker::clone() const{
	return new BehaviorControlsBlocker(*this);
}

/*!
\fn     void BehaviorControlsBlocker::setTime(float time)
\param  time
          time
\brief  See BehaviorControlsBlocker.h
*/
void BehaviorControlsBlocker::setTime(float time){
	this -> time = time;
}