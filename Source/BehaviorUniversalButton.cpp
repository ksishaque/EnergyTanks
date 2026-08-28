/*!
\file   BehaviorUniversalButton.cpp
\author Kevin Shin
\date   2-13-2023
\brief
        Functions for managing the behavior of a player-controlled object
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include <glfw/glfw3.h>

#include "ActionNode.h"
#include "ControlManager.h"
#include "Trace.h"

#include "BehaviorUniversalButton.h"

/*!
\fn     BehaviorUniversalButton::BehaviorUniversalButton(int button)
\param  button
          key
\brief  See BehaviorUniversalButton.h
*/
BehaviorUniversalButton::BehaviorUniversalButton(int button) : Behavior(), button(button), claim(false), list(new ActionNode *[3]){

	//	Set nodes to `nullptr`
	list[0] = nullptr;
	list[1] = nullptr;
	list[2] = nullptr;

}

/*!
\fn     BehaviorUniversalButton::BehaviorUniversalButton(const BehaviorUniversalButton &that)
\param  that
          source
\brief  See BehaviorUniversalButton.h
*/
BehaviorUniversalButton::BehaviorUniversalButton(const BehaviorUniversalButton &that) : Behavior(), button(that.button), claim(false), list(new ActionNode *[3]){

	//	Copy nodes
	if(that.list[0]) list[0] = that.list[0] -> clone();
	else list[0] = nullptr;
	if(that.list[1]) list[1] = that.list[1] -> clone();
	else list[1] = nullptr;
	if(that.list[2]) list[2] = that.list[2] -> clone();
	else list[2] = nullptr;

}

/*!
\fn    BehaviorUniversalButton::~BehaviorUniversalButton()
\brief See BehaviorUniversalButton.h
*/
BehaviorUniversalButton::~BehaviorUniversalButton(){

	//	Release key
	if(claim) ControlManager::getInstance() -> releaseKey(button);

	//	Delete list
	delete [] list;

}

/*!
\fn     void BehaviorUniversalButton::update(float dt)
\param  dt
          dt
\brief  See BehaviorUniversalButton.h
*/
void BehaviorUniversalButton::update(float dt){

	//	Check if already claimed or invalid button
	if(claim || button < 0) return;

	//	Variable: Singleton instance of the control manager
	ControlManager *con = ControlManager::getInstance();

	//	Try to claim new key
	claim = con -> claimKey(button);

	//	Check for success
	if(claim){

		//	Add actions
		if(list[0]) con -> addAction(list[0], button, ControlManager::KeyState::RELEASED);
		if(list[1])con -> addAction(list[1], button, ControlManager::KeyState::PRESSED);
		if(list[2])con -> addAction(list[2], button, ControlManager::KeyState::HELD);

	}

}

/*!
\fn     void BehaviorUniversalButton::addAction(ActionNode *node, int state)
\param  node
          action
\param  state
          keyState
\brief  See BehaviorUniversalButton.h
*/
void BehaviorUniversalButton::addAction(ActionNode *node, int state){

	//	Check state
	if(state < 0 || state > 2) return;

	//	Check for match case
	if(claim) ControlManager::getInstance() -> addAction(node, button, (ControlManager::KeyState) state);

	//	Start `list[state]`
	if(list[state] == nullptr) list[state] = node;

	//	Add to `list[state]`
	else list[state] -> operator<<(*node);

}

/*!
\fn     void BehaviorUniversalButton::setButton(int key)
\param  key
          key
\brief  See BehaviorUniversalButton
*/
void BehaviorUniversalButton::setButton(int key){

	//	Release previous button
	if(claim) ControlManager::getInstance() -> releaseKey(button);
	claim = false;

	//	Set `button`
	button = key;

	//	Try to set
	update(0);

}

/*!
\fn     BehaviorUniversalButton *BehaviorUniversalButton::clone()
\brief  See Component.h
*/
BehaviorUniversalButton *BehaviorUniversalButton::clone() const{
	return new BehaviorUniversalButton(*this);
}