/*!
\fnile  ShutdownSystem.cpp
\author Kevin Shin (kevin.shin\@digipen.edu)
\date   4-7-2023
\brief
        Functions for creating and maintaining an object culler for the object manager
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "BehaviorPopup.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include "ObjectManager.h"

#include "ShutdownSystem.h"

/*!
\fn     void ShutdownSystem::initialize()
\brief  See ISystem.h
*/
void ShutdownSystem::initialize(){

	//	Initialize system
	if(isActive()) return;
	ISystem::initialize();

	//	Initialize `popup`
	popup = parseObject("Shutdown PopUp");

	//	Variable: Behavior of `popup`
	BehaviorPopup *bhv = dynamic_cast<BehaviorPopup *>(popup -> get(ComponentTypeEnum::cBehavior));

	//	Check `bhv`
	if(bhv == nullptr){

		//	Delete `popup`
		delete popup;
		popup = nullptr;

		//	Return
		return;

	}

	//	Set as unpausable
	bhv -> setPAWSable(false);

	//	Add `popup` to the manager
	ObjectManager::getInstance() -> addForeignObject(popup);

}

/*!
\fn     void ShutdownSystem::shutdown()
\brief  See ISystem.h
*/
void ShutdownSystem::shutdown(){

	//	Shutdown system
	if(!isActive()) return;
	ISystem::shutdown();

	//	Delete and nullify `popup`
	delete popup;
}

/*!
\fn     ShutdownSystem::ShutdownSyste)
\brief  See ShutdownSystem.h
*/
ShutdownSystem::ShutdownSystem() : ISystem(sShutdown), popup(nullptr){}

/*!
\fn     void ShutdownSystem::initiateShutdown()
\brief  See ShutdownSystem.h
*/
void ShutdownSystem::initiateShutdown(){

	//	Check if the system has been properly initialized
	if(!isActive() || popup == nullptr) return;

	//	Variable: Behavior of `popup`
	BehaviorPopup *bhv = dynamic_cast<BehaviorPopup *>(popup -> get(ComponentTypeEnum::cBehavior));

	//	Check `bhv`
	if(bhv == nullptr){

		//	Delete `popup`
		delete popup;
		popup = nullptr;

		//	Return
		return;

	}

	//	Open `popup`
	bhv -> open();

}

/*!
\fn     ShutdownSystem *ShutdownSystem::getInstance()
\brief  See ShutdownSystem.h
*/
ShutdownSystem *ShutdownSystem::getInstance(){

	//	Initialize the instance, if needed
	if(instance == nullptr) instance = new ShutdownSystem();

	//	Return
	return instance;

}

/*!
\var    instance
          See ShutdownSystem.h
*/
ShutdownSystem *ShutdownSystem::instance = nullptr;

/*!
\fn     void ShutdownSystem::closeInstance()
\brief  See ShutdownSystem.h
*/
void ShutdownSystem::closeInstance(){

	//	Delete `instance`
	delete instance;
	instance = nullptr;

}