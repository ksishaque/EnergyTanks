/*!
\file   ControlManager.cpp
\author Kevin Shin
\date   1-13-2023
\brief
        Functions for general use
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

#include <glfw/glfw3.h>
#include <stdexcept>

#include "ActionList.h"
#include "Controller.h"
#include "ControllerButtons.h"
#include "Trace.h"
#include "Window.h"

#include "ControlManager.h"

/*!
\fn     static void processKeyEvent(GLFWwindow *win, int key, int scan, int act, int mod)
\param  win
          window
\param  key
          key
\param  scan
          scancode
\param  act
          action
\param  mod
          mods
\brief  See ControlManager.h
*/
static void processKeyEvent(GLFWwindow *win, int key, int scan, int act, int mod){

	//	Ignore `GLFW_REPEAT`
	if(act != GLFW_REPEAT){

		//	Do action for all keys
		ControlManager::instance -> keyActions[0][act].update(0);

		//	Check for invalid key
		if(key < 0) return;

		//	Do action based on `key` and `act`
		ControlManager::instance -> keyActions[key][act].update(0);

		//	Update held status of the key
		ControlManager::instance -> keyDowns[key] = (bool) act;

	}

}

/*!
\fn     ControlManager::ControlManager()
\brief  See ControlManager.h
*/
ControlManager::ControlManager() : ISystem(sConMan), window(Window::getInstance() -> getHandle()), keyActions(new ActionList*[GLFW_KEY_LAST + 1]), keyClaims(new bool[GLFW_KEY_LAST + 1]), keyDowns(new bool[GLFW_KEY_LAST + 1]), controllers(), removedControllers(){

	//	Set `keyActions`
	for(unsigned i = 0; i <= GLFW_KEY_LAST; i += 1) keyActions[i] = new ActionList[3]();

	//	Initialize per key
	for(int i = 0; i <= GLFW_KEY_LAST; i += 1){

		//	Initialize `keyClaims`
		keyClaims[i] = false;

		//	Initialize `keyDowns`
		keyDowns[i] = false;

	}

}

/*!
\fn     void ControlManager::shutdown()
\brief  See ControlManager.h
*/
void ControlManager::shutdown(){

	//	Remove callbacks
	glfwSetKeyCallback(window, nullptr);
	glfwSetJoystickCallback(nullptr);

	//	Unset `window`
	window = nullptr;

	//	Clear all actions
	for(int i = 0; i <= GLFW_KEY_LAST; i += 1) for(int j = 0; j < 3; j += 1) keyActions[i][j].clear();

	//	Delete all controllers
	for(std::pair<int, Controller*> controller : controllers) delete controller.second;
	controllers.clear();
	removedControllers.clear();

}

/*!
\fn     ControlManager::~ControlManager()
\brief  See ControlManager.h
*/
ControlManager::~ControlManager(){

	//	Delete `keyActions`
	for(int i = 0; i <= GLFW_KEY_LAST; i += 1) delete[] keyActions[i];
	delete[] keyActions;

	//	Delete `keyClaims` and `keyDowns`
	delete[] keyClaims;
	delete[] keyDowns;

}

/*!
\fn     void ControlManager::addAction(ActionNode *node, int key, ControlManager::KeyState state)
\param  node
          node
\param  key
          key
\param  state
          state
\brief  See ControlManager
*/
void ControlManager::addAction(ActionNode *node, int key, ControlManager::KeyState state){
	keyActions[key][state].add(node);
}

/*!
\fn     bool ControlManager::claimKey(int key)
\param  key
          key
\param  cont
          controller
\brief  See ControlManager
*/
bool ControlManager::claimKey(int key){

	//	Variable: Return value / if the key is unclaimed
	bool ans = !keyClaims[key];

	//	Claim key
	keyClaims[key] = true;

	//	Return
	return ans;

}

/*!
\fn     static void processJoystickEvent(int js, int e)
\param  js
          joystick
\param  e
          event
\brief  See ControlManager.h
*/
static void processJoystickEvent(int js, int e){

	//	Add the controller
	if(e == GLFW_CONNECTED){
		
#ifdef DEBUG_SYSTEM
		Trace::message("Controller %d connected", js);
#endif

		//	Create and add the new controller
		ControlManager::instance -> controllers.emplace(js, new Controller(js));

	}

	//	Remove the controller
	else{

		//	Set to delete
		ControlManager::instance -> removedControllers.push_front(js);
		
#ifdef DEBUG_SYSTEM
		Trace::message("Controller %d disconnected", js);
		Trace::message("Controllers: %d", ControlManager::instance -> controllers.size());
#endif

	}

}

/*!
\fn     void ControlManager::update(float dt)
\param  dt
          dt
\brief  See ControlManager.h
*/
void ControlManager::update(float &dt){

	//	Check `window`
	if(window == nullptr){

		//	Try to set `window` again
		window = Window::getInstance() -> getHandle();

		//	Check again
		if(window == nullptr) return;
		
		//	Set callbacks
		glfwSetKeyCallback(window, processKeyEvent);
		glfwSetJoystickCallback(processJoystickEvent);

	}

	//	Set universal button
	keyDowns[0] = false;
	
#ifdef DEBUG_SYSTEM
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) Trace::message("==========================================================================================");
#endif

	//	Handle control events
	glfwPollEvents();

	//	Update `controllers`
	for(std::pair<int, Controller *> controller : controllers) controller.second -> update(dt);

	//	Delete disconnected controllers
	for(int removedController : removedControllers){

		//	Attempt delete
		try{

			//	Variable: Controller to delete
			Controller *cont = controllers.at(removedController);

			//	Delete
			controllers.erase(removedController);
			delete cont;

		}
		catch(const std::out_of_range &){}

	}
	removedControllers.clear();

	//	Check for held keys
	for(unsigned i = 1; i <= GLFW_KEY_LAST; i += 1) if(keyDowns[i]){
		
		//	Process held key output
		keyActions[i][KeyState::HELD].update(dt);

		//	Set universal button as held
		keyDowns[0] = true;

	}

	//	Check if universal button is held
	if(keyDowns[0]) keyActions[0][KeyState::HELD].update(dt);

}

/*!
\fn     ControlManager *ControlManager::getInstance()
\brief  See ControlManager.h
*/
ControlManager *ControlManager::getInstance(){

	//	Check and make `instance`
	if(instance == nullptr) instance = new ControlManager();

	//	Return
	return instance;

}

/*!
\fn     void ControlManager::closeInstance()
\brief  See ControlManager.h
*/
void ControlManager::closeInstance(){

	//	Delete and clear `instance`
	delete instance;
	instance = nullptr;

}

/*!
\var    instance
\brief  See ControlManager.h
*/
ControlManager *ControlManager::instance = nullptr;

/*!
\fn     void ControlManager::releaseKey(int key)
\param  key
          key
\brief  See ControlManager
*/
void ControlManager::releaseKey(int key){

	//	Release claim
	keyActions[key][KeyState::RELEASED].update(0);
	keyClaims[key] = false;

	//	Clear key
	for(int i = 0; i < 3; i += 1) clearAction(key, static_cast<KeyState>(i));

}

/*!
\fn     void ControlManager::clearAction(int key, ControlManager::KeyState state)
\param  key
          key
\param  state
          state
\param  cont
          controller
\brief  See ControlManager
*/
void ControlManager::clearAction(int key, ControlManager::KeyState state){
	keyActions[key][state].clear();
}

/*!
\fn     void ControlManager::reupdateKey(int key)
\param  key
          key
\brief  See ControlManager
*/
void ControlManager::reupdateKey(int key){
	keyActions[key][KeyState::PRESSED].update(0);
}

/*!
\fn     void ControlManager::universalInput(ControlManager::KeyState state)
\param  state
          state
\brief  See ControlManager
*/
void ControlManager::universalInput(ControlManager::KeyState state){

	//	Check for `held`
	if(state == KeyState::HELD){

		//	Set universal button as held
		keyDowns[0] = true;

		//	Return
		return;

	}

	//	Run universal actions
	keyActions[0][state].update(0);

}

/*!
\fn     void ControlManager::initialize()
\brief  See ControlManager.h
*/
void ControlManager::initialize(){

	//	Variable: Loop control variable / joystick ID to search for
	int js = 0;

	//	Create controllers for each joystick found
	while(glfwJoystickPresent(js)){

		//	Create controller
		controllers.emplace(js, new Controller(js));

		//	Increment `js`
		js += 1;

	}

}

/*!
\fn     bool ControlManager::setControllerUnit(int cont, ControlUnit *u)
\param  cont
          controller
\param  u
          unit
\brief  See ControlManager.h
*/
bool ControlManager::setControllerUnit(int cont, ControlUnit *u){

	//	Attempt to find controller
	try{

		//	Set the controller's `unit`
		controllers.at(cont) -> setUnit(u);

		//	Return
		return true;

	}
	catch(const std::out_of_range &){}

	//	Return
	return false;

}

/*!
\fn     bool ControlManager::checkKey(int key)
\param  key
          key
\brief  See ControlManager
*/
bool ControlManager::checkKey(int key){
	return keyDowns[key];
}

/*!
\fn     void ControlManager::manualControllerCall(int cont, KeyState state)
\param  cont
          controller
\param  state
          state
\brief  See ControlManager.h
*/
void ControlManager::manualControllerCall(int cont, KeyState state){

	//	Attempt to find controller
	try{

		//	Set the controller's `unit`
		controllers.at(cont) -> manualCall(state);

	}
	catch(const std::out_of_range &){}

}