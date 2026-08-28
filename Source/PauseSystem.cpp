/*!
\fnile  PauseSystem.cpp
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   4-9-2023
\brief
        Functions for creating and maintaining a pause system
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include <glfw/glfw3.h>

#include "BehaviorPopup.h"
#include "DebugSystem.h"
#include "GameObject.h"
#include "SoundSystem.h"
#include "ObjectFactory.h"
#include "ObjectManager.h"
#include "Window.h"

#include "PauseSystem.h"

/*!
\fn     static void focusPause(GLFWwindow *handle, int focus)
\param  handle
          window
\param  focus
          isFocused
\brief  See PauseMenu.h
*/
static void focusPause(GLFWwindow *handle, int focus){

#ifndef _DEBUG

	//	Unpause if focused
	if(focus){
		
		//	Unpause
		PauseSystem::instance -> unpauseLite();

		//	Disable cursor
		glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		
		//	Resume sounds
		SoundSystem::pauseAll(false);

		//	Unblock
		PauseSystem::instance -> blocked = false;

	}

	//	Pause if unfocused
	else{
		
		//	Pause
		PauseSystem::instance -> pause(true);

		//	Re-enable cursor
		glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		
		//	Pause sounds
		SoundSystem::pauseAll(true);

		//	Block
		PauseSystem::instance -> blocked = true;

		//	Check `popup`
		if(PauseSystem::instance -> popup){

			//	Update `popup` to start it
			PauseSystem::instance -> popup -> update(0);
			PauseSystem::instance -> popup -> update(0);
			
		}

	}

#endif

}

/*!
\fn     void PauseSystem::initialize()
\brief  See ISystem.h
*/
void PauseSystem::initialize(){

	//	Initialize system
	if(isActive()) return;
	ISystem::initialize();

	//	Initialize `backup`
	backup = parseObject("Pause Lite");

	//	Add `popup` to the manager
	ObjectManager::getInstance() -> addForeignObject(backup);

	//	Set callback
	glfwSetWindowFocusCallback(Window::getInstance() -> getHandle(), focusPause);

}

/*!
\fn     void PauseSystem::shutdown()
\brief  See ISystem.h
*/
void PauseSystem::shutdown(){

	//	Pause system
	if(!isActive()) return;
	ISystem::shutdown();

	//	Delete and nullify `backup`
	delete backup;
}

/*!
\fn     PauseSystem::PauseSyste)
\brief  See PauseSystem.h
*/
PauseSystem::PauseSystem() : ISystem(sPause), paused(false), blocked(false), trueDt(0), popup(nullptr), backup(nullptr){}

/*!
\fn     void PauseSystem::pause(bool paused)
\param  paused
          state
\brief  See PauseSystem.h
*/
void PauseSystem::pause(bool paused){

	//	Check if the system has been properly initialized
	if(!isActive() || backup == nullptr || paused == this -> paused) return;

	//	Check `paused`
	if(paused){

		//	Find `popup`
		popup = ObjectManager::getInstance() -> findObject("Pause PopUp");

		//	Set `backup`
		if(popup == nullptr) popup = backup;

		//	Variable: Behavior of `popup`
		BehaviorPopup *bhv = dynamic_cast<BehaviorPopup *>(popup -> get(ComponentTypeEnum::cBehavior));

		//	Check `bhv`
		if(bhv == nullptr) return;

		//	Exclude and open
		bhv -> setPAWSable(false);
		bhv -> open();

		//	Mute
		SoundSystem::muteMusic(true);

	}
	else{

		//	Check `popup`
		if(popup){

			//	Variable: Behavior of `popup`
			BehaviorPopup *bhv = dynamic_cast<BehaviorPopup *>(popup -> get(ComponentTypeEnum::cBehavior));

			//	Close `popup`
			if(bhv) bhv -> setToClose();

			//	Release `popup`
			popup = nullptr;

		}

		//	Unmute
		SoundSystem::muteMusic(false);

	}

	//	Set	`paused`
	this -> paused = paused;

}

/*!
\fn     PauseSystem *PauseSystem::getInstance()
\brief  See PauseSystem.h
*/
PauseSystem *PauseSystem::getInstance(){

	//	Initialize the instance, if needed
	if(instance == nullptr) instance = new PauseSystem();

	//	Return
	return instance;

}

/*!
\var    instance
          See PauseSystem.h
*/
PauseSystem *PauseSystem::instance = nullptr;

/*!
\fn     void PauseSystem::closeInstance()
\brief  See PauseSystem.h
*/
void PauseSystem::closeInstance(){

	//	Delete `instance`
	delete instance;
	instance = nullptr;

}

/*!
\fn     void update(float &dt)
\param  dt
          dt
\brief  See ISystem.h
*/
void PauseSystem::update(float &dt){

	//	Cap `dt`
	if(dt > 0.0625f
#ifdef DEBUG_SYSTEM
		&& !DebugSystem::getInstance() -> getFlag(DebugSystem::DebugFlag::MANUAL_LAG)
#endif
		) dt = 0.0625f;

	//	Save `trueDt`
	trueDt = dt;

	//	Block if necessary
	while(blocked) glfwWaitEvents();

	//	Reduce `dt` to 0
	if(paused) dt = 0;

}

/*!
\fn     void PauseSystem::pause()
\brief  See PauseSystem.h
*/
void PauseSystem::pause(){
	pause(!paused);
}

/*!
\fn     void PauseSystem::pauseFull()
\brief  See PauseSystem.h
*/
void PauseSystem::pauseFull(){

	//	Check if the system has been properly initialized
	if(!isActive()) return;

	//	Close `backup`
	if(popup == backup) pause(false);

	//	Open if closed
	if(!paused){

		//	Find `popup`
		popup = ObjectManager::getInstance() -> findObject("Pause PopUp");

		//	Check `popup`
		if(popup == nullptr) return;

		//	Variable: Behavior of `popup`
		BehaviorPopup *bhv = dynamic_cast<BehaviorPopup *>(popup -> get(ComponentTypeEnum::cBehavior));

		//	Check `bhv`
		if(bhv == nullptr) return;

		//	Exclude and open
		bhv -> setPAWSable(false);
		bhv -> open();

		//	Set `paused`
		paused = true;

		//	Mute
		SoundSystem::muteMusic(true);

	}

}

/*!
\fn     bool PauseSystem::isPaused()
\brief  See PauseSystem.h
*/
bool PauseSystem::isPaused(){
	return !isActive() || paused;
}

/*!
\fn     float PauseSystem::getDt()
\brief  See PauseSystem.h
*/
float PauseSystem::getDt(){
	return trueDt;
}

/*!
\fn     void PauseSystem::unpauseLite()
\brief  See PauseSystem.h
*/
void PauseSystem::unpauseLite(){

	//	Check if the system has been properly initialized
	if(!isActive()) return;

	//	Close `backup`
	if(popup == backup) pause(false);

}