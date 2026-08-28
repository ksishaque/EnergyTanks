/*!
\file   BehaviorControllable.cpp
\author Kevin Shin
\date   2-13-2023
\brief
        Functions for managing the behavior of a player-controlled object
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include <glfw/glfw3.h>

#include "TeamSystem.h"
#include "Trace.h"

#include "BehaviorControllable.h"

/*!
\fn     BehaviorControllable::BehaviorControllable(int up, int dn, int lf, int rt, int sh, float cd, float sp)
\param  up
          up
\param  dn
          down
\param  lf
          left
\param  rt
          right
\param  act
          action
\param  cd
          cooldown
\brief  See BehaviorControllable.h
*/
BehaviorControllable::BehaviorControllable() : Behavior(), deleting(false), teamSet(false), hadControl(false), priority(0), controls(nullptr){}

/*!
\fn     void BehaviorControllable::update(float dt)
\param  dt
          dt
\brief  See BehaviorControllable.h
*/
void BehaviorControllable::update(float dt){

	//	Variable: Parent of the behavior
	GameObject* parent = getParent();

	//	Check `parent`
	if(parent && !teamSet) teamSet = TeamSystem::getInstance() -> setPlayer(parent -> getTeam(), this);

	//	Update `controls`
	if(controls) controls -> update();

}

/*!
\fn     void BehaviorControllable::setControlUnit(ControlUnit *unit)
\param  unit
          unit
\brief  See BehaviorControllable.h
*/
void BehaviorControllable::setControlUnit(ControlUnit *unit){

	//	Check `unit` and set behavior
	if(unit && unit -> setBehavior(this)){

		//	Release current unit
		releaseControlUnit();

		//	Set `controls`
		controls = unit;

		//	Call `gainControl` and set `hadControl`
		if(hadControl) gainControl();
		hadControl = true;

	}

}

/*!
\fn    BehaviorControllable::~BehaviorControllable()
\brief See BehaviorControllable.h
*/
BehaviorControllable::~BehaviorControllable(){

	//	Set `deleting`
	deleting = true;

	//	Remove behavior from team
	if(teamSet){

		//	Variable: Parent of the behavior
		GameObject* parent = getParent();

		//	Check `parent`
		if(parent) TeamSystem::getInstance() -> removePlayer(parent -> getTeam(), this);

	}

	//	Release `controls`
	releaseControlUnit();

}

/*!
\fn     ControlUnit *BehaviorControllable::getControlUnit()
\brief  See BehaviorControllable.h
*/
ControlUnit *BehaviorControllable::getControlUnit(){
	return controls;
}

/*!
\fn     ControlUnit * BehaviorControllable::getControlUnit()
\brief  See BehaviorControllable.h
*/
ControlUnit *BehaviorControllable::releaseControlUnit(){

	//	Variable: Return value / `controls` before releasing
	ControlUnit *ans = controls;

	//	Remove `controls`
	if(controls){

		//	Call `loseControl()`
		loseControl();

		//	Unset behavior
		controls -> setBehavior(deleting);

		//	Set `controls`
		controls = nullptr;

	}

	//	Return
	return ans;

}

/*!
\fn     void BehaviorControllable::setPriority(int prior)
\param  prior
          priority
\brief  See BehaviorControllable.h
*/
void BehaviorControllable::setPriority(int prior){
	priority = prior;
}

/*!
\fn     int BehaviorControllable::getPriority()
\brief  See BehaviorControllable.h
*/
int BehaviorControllable::getPriority(){
	return priority;
}