/*!
\file   ControlUnit.cpp
\author Kevin Shin
\date   3-17-2023
\brief
        Functions for managing a player's control scheme
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "AddToAction.h"
#include "BehaviorControllable.h"
#include "ControllerButtons.h"
#include "ControlManager.h"
#include "ControlUnitAction.h"

#include "ControlUnit.h"

#define DN DOWN
#define LF LEFT
#define RT RIGHT
#define A1 FIRST
#define A2 SECOND

#include "GameObject.h"

/*!
\fn     ControlUnit::ControlUnit(int up, int dn, int lf, int rt, int sh, float cd, float sp)
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
\brief  See ControlUnit.h
*/
ControlUnit::ControlUnit(int up, int dn, int lf, int rt, int a1, int a2) : inUD(0), inLR(0), fullClaim(false), behavior(nullptr), controller(-1){

	//	Set `keys`
	keys[ControlType::UP] = up;
	keys[ControlType::DN] = dn;
	keys[ControlType::LF] = lf;
	keys[ControlType::RT] = rt;
	keys[ControlType::A1] = a1;
	keys[ControlType::A2] = a2;

	//	Set `claims` and `visKeys`
	for(unsigned i = 0; i < CONTROL_UNIT_KEY_MAX; i += 1){

		//	Set `claims`
		claims[i] = false;

		//	Set `visKeys`
		visKeys[i] = keys[i];

	}

}

/*!
\fn     void ControlUnit::attemptClaim(int key, bool &claim, ControlType act, int &axis, int val)
\param  key
          key
\param  claim
          claim
\param  act
          action
\param  axis
          axis
\param  val
          value
\return Nothing
\brief
        This function attempts to claim a directional key.
*/
void ControlUnit::attemptClaim(int key, bool &claim, ControlType act, int &axis, int val){

	//	Check if already claimed
	if(claim) return;

	//	Variable: Singleton control manager, for convenience
	ControlManager *cont = ControlManager::getInstance();

	//	Try to claim new key
	claim = cont -> claimKey(key);

	//	Set right key actions
	if(claim){

		//	Set key actions
		cont -> addAction(addTo(axis, val), key, ControlManager::KeyState::PRESSED);
		cont -> addAction(new ControlUnitAction(this, act, ControlManager::KeyState::PRESSED), key, ControlManager::KeyState::PRESSED);
		cont -> addAction(addTo(axis, -val), key, ControlManager::KeyState::RELEASED);
		cont -> addAction(new ControlUnitAction(this, act, ControlManager::KeyState::RELEASED), key, ControlManager::KeyState::RELEASED);
		
		//	Update key state
		cont -> reupdateKey(key);

		//	Set `visKeys`
		visKeys[act] = key;

	}

}

/*!
\fn     void attemptClaim(int key, bool &claim, int &axis, int val)
\param  key
          key
\param  claim
          claim
\param  act
          action
\brief  See ControlUnit.h
*/
void ControlUnit::attemptClaim(int key, bool &claim, ControlType act){

	//	Check if already claimed
	if(claim) return;

	//	Variable: Singleton control manager, for convenience
	ControlManager *cont = ControlManager::getInstance();

	//	Try to claim new key
	claim = cont -> claimKey(key);

	//	Set right key actions
	if(claim){

		//	Set key actions
		cont -> addAction(new ControlUnitAction(this, act, ControlManager::KeyState::PRESSED), key, ControlManager::KeyState::PRESSED);
		cont -> addAction(new ControlUnitAction(this, act, ControlManager::KeyState::HELD), key, ControlManager::KeyState::HELD);
		cont -> addAction(new ControlUnitAction(this, act, ControlManager::KeyState::RELEASED), key, ControlManager::KeyState::RELEASED);
		
		//	Update key state
		cont -> reupdateKey(key);

		//	Set `visKeys`
		visKeys[act] = key;

	}

}

/*!
\fn     void ControlUnit::update()
\brief  See ControlUnit.h
*/
void ControlUnit::update(){
	
	//	TEMPORARY — TO BE DELETED
	if(behavior && behavior -> getParent()){
		if(behavior -> getParent() -> getTeam() == GameObject::Team::Left) setController(0);
		else if(behavior -> getParent() -> getTeam() == GameObject::Team::Right) setController(1);
	}

	//	Attempt to claim all keys
	if(!fullClaim){

		//	Claim directional keys
		attemptClaim(keys[ControlType::UP], claims[ControlType::UP], UP, inUD, 1);
		attemptClaim(keys[ControlType::DN], claims[ControlType::DN], DN, inUD, -1);
		attemptClaim(keys[ControlType::LF], claims[ControlType::LF], LF, inLR, 1);
		attemptClaim(keys[ControlType::RT], claims[ControlType::RT], RT, inLR, -1);

		//	Claim action keys
		attemptClaim(keys[ControlType::A1], claims[ControlType::A1], A1);
		attemptClaim(keys[ControlType::A2], claims[ControlType::A2], A2);

		//	Update `fullClaim`
		fullClaim = true;
		for(unsigned i = 0; i < CONTROL_UNIT_KEY_MAX; i += 1) if(!claims[i]) fullClaim = false;

	}

	//	Check `inUD` and `inLR`
	if(behavior){

		//	Check `inUD`
		if(inUD > 0) behavior -> actionCall(ControlType::UP);
		else if(inUD < 0) behavior -> actionCall(ControlType::DN);
		else behavior -> actionCall(ControlType::Y_NEUTRAL);

		//	Check `inLR`
		if(inLR > 0) behavior -> actionCall(ControlType::LF);
		else if(inLR < 0) behavior -> actionCall(ControlType::RT);
		else behavior -> actionCall(ControlType::X_NEUTRAL);

	}

}

/*!
\fn     void ControlUnit::setKey(ControlType i, int key)
\param  i
          control
\param  key
          key
\brief  See ControlUnit.h
*/
void ControlUnit::setKey(ControlType i, int key){

	//	Check for match case
	if(i < 0 || i >= CONTROL_UNIT_KEY_MAX || keys[i] == key || key < 0) return;

	//	Release claim
	if(claims[i]) ControlManager::getInstance() -> releaseKey(keys[i]);

	//	Set new key
	keys[i] = key;
	claims[i] = false;
	fullClaim = false;

}

/*!
\fn    ControlUnit::~ControlUnit()
\brief See ControlUnit.h
*/
ControlUnit::~ControlUnit(){

	//	Variable: Singleton control manager, for convenience
	ControlManager *col = ControlManager::getInstance();

	//	Unset `unit` for `controller`
	col -> setControllerUnit(controller);

	//	Release claims
	for(unsigned i = 0; i < CONTROL_UNIT_KEY_MAX; i += 1) if(claims[i]) col -> releaseKey(keys[i]);

}

/*!
\fn     void ControlUnit::actionCall()
\brief  See ControlUnit.h
*/
void ControlUnit::actionCall(ControlType action, ControlManager::KeyState keyState){
	if(behavior) behavior -> actionCall(action, keyState);
}

/*!
\fn     int ControlUnit::getKey(ControlType i) const
\param  i
          control
\brief  See ControlUnit.h
*/
int ControlUnit::getKey(ControlType i) const{

	//	Check invalid case
	if(i < 0 || i >= CONTROL_UNIT_KEY_MAX) return -1;

	//	Return
	return visKeys[i];

}

/*!
\fn     bool ControlUnit::setBehavior(BehaviorControllable *behavior)
\param  behavior
          behavior
\brief  See ControlUnit.h
*/
bool ControlUnit::setBehavior(BehaviorControllable *behavior){

	//	Check `behavior`
	if(this -> behavior) return false;

	//	Set new key
	this -> behavior = behavior;

	//	Update new behavior
	if(behavior){

		//	Variable: Singleton instance of the control manager, for convenience
		ControlManager *cont = ControlManager::getInstance();
		
		//	Update key states
		for(unsigned i = 0; i < CONTROL_UNIT_KEY_MAX; i += 1) if(cont -> checkKey(keys[i])) behavior -> actionCall((ControlType) i, ControlManager::KeyState::PRESSED);

		//	Re-press `controller` buttons
		//cont -> manualControllerCall(controller, ControlManager::KeyState::PRESSED);

	}

	//	Return
	return true;

}

/*!
\fn     bool ControlUnit::setBehavior(bool skip)
\param  skip
          update
\brief  See ControlUnit.h
*/
bool ControlUnit::setBehavior(bool skip){

	//	Update old behavior
	if(behavior && !skip){

		//	Variable: Singleton instance of the control manager, for convenience
		ControlManager *cont = ControlManager::getInstance();
		
		//	Update key states
		for(unsigned i = 0; i < CONTROL_UNIT_KEY_MAX; i += 1) if(cont -> checkKey(keys[i])) behavior -> actionCall((ControlType) i, ControlManager::KeyState::RELEASED);

		//	Re-press `controller` buttons
		cont -> manualControllerCall(controller, ControlManager::KeyState::RELEASED);

		//	Send neutral calls
		behavior -> actionCall(ControlType::Y_NEUTRAL);
		behavior -> actionCall(ControlType::X_NEUTRAL);

	}

	//	Set new key
	behavior = nullptr;

	//	Return
	return true;

}

/*!
\fn     const int *ControlUnit::getKeyReference(ControlType i) const
\param  i
          control
\brief  See ControlUnit.h
*/
const int *ControlUnit::getKeyReference(ControlType i) const{
	return visKeys + i;
}

/*!
\fn     void ControlUnit::setController(int c)
\param  c
          controller
\brief  See ControlUnit.h
*/
void ControlUnit::setController(int c){

	//	Check `controller`
	if(controller == c) return;

	//	Unset `unit` for `controller`
	ControlManager::getInstance() -> setControllerUnit(controller);

	//	Check for release case
	if(c == -1){

		//	Release controller
		controller = -1;

		//	Return
		return;

	}

	//	Check for `c`
	if(!ControlManager::getInstance() -> setControllerUnit(c, this)) return;

	//	Check `c`
	if(c < 0) for(unsigned i = 0; i < CONTROL_UNIT_KEY_MAX; i += 1) visKeys[i] = keys[i];
	else{

		//	Set `visKeys`
		visKeys[ControlType::UP] = CTRL_KEY_LS_UP;
		visKeys[ControlType::DOWN] = CTRL_KEY_LS_DOWN;
		visKeys[ControlType::LEFT] = CTRL_KEY_LS_LEFT;
		visKeys[ControlType::RIGHT] = CTRL_KEY_LS_RIGHT;
		visKeys[ControlType::FIRST] = CTRL_KEY_RT;
		visKeys[ControlType::SECOND] = CTRL_KEY_BACK;

	}

	//	Set `controller`
	controller = c;

}

/*!
\fn     void ControlUnit::iterateAxisY(int val)
\param  val
          value
\brief  See ControlUnit.h
*/
void ControlUnit::iterateAxisY(int val){
	inUD += val;
}

/*!
\fn     void ControlUnit::iterateAxisX(int val)
\param  val
          value
\brief  See ControlUnit.h
*/
void ControlUnit::iterateAxisX(int val){
	inLR += val;
}