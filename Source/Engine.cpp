/*!
\file   Engine.cpp
\author Kevin Shin
\date   9-13-2022
\brief
        Functions for setting up and running an engine
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "glfw/glfw3.h"

#include <algorithm>

#include "Collider.h"
#include "General.h"
#include "ObjectManager.h"
#include "Trace.h"
#include "Window.h"
#include "TeamSystem.h"
//#include "ControllerInput.h"

#include "Engine.h"

#ifdef _DEBUG
//	Debug breakpoint forward declaration
void debugBreak(const ObjectManager *, const Engine *);
#endif

/*!
\fn     void addSystem(ISystem *sys)
\param  sys: system
\brief  See Engine.h
*/
void Engine::addSystem(ISystem *sys){
	
	//	Check `sys`
	if(sys == nullptr) return;
	
	//	Add `sys` to `systems` and set parent
	systems.push_back(sys);
	sys->setParent(this);
	
	//	Initialize and sort if the engine is already running
	if(isRunning){
	
		//	Initialize and add `sys` to `shutdownStack`
		sys -> initialize();
		shutdownStack.push(sys);
	
		//	Sort `system`
		std::sort(systems.begin(), systems.end(), pointerCompare<ISystem>);
	}
}

/*!
\fn     void Engine::initialize()
\brief  See Engine.h
*/
void Engine::initialize(){
	
	//	Initialize every system
	for(ISystem *system : systems){
	
		//	Initialize `system`
		system -> initialize();
	
		//	Add `system` to `shutdownStack`
		shutdownStack.push(system);
	}
	
	//	Set to run
	isRunning = true;
	
	//	Sort `system`
	std::sort(systems.begin(), systems.end(), [](ISystem *s1, ISystem *s2){
		return *s1 < *s2;
	});
	
	//	Variable: time of previous frame
	double time = glfwGetTime();
	
	//	Begin running
	while(isRunning){
		
		/*	Variables:
		newTime: current time
		dt: time since previous frame
		*/
		double newTime = glfwGetTime();
	    float dt = float(newTime - time);
	
		//	Record current time
		time = newTime;

        //if(isColliding(collider1, collider2)) Trace::message("\t[ColTest]: collision detected!");
	
		//	Update
	    update(dt);
        //Sleep(200);
	}

	//	Shutdown engine
	shutdown();
}

/*!
\fn     void Engine::update(float dt)
\param  dt
          dt
\brief  See Engine.h
*/
void Engine::update(float &dt){

	//	Update each system
	for(ISystem *system : systems) system -> update(dt);

#ifdef _DEBUG
	//	Debug breakpoint
	debugBreak(dynamic_cast<ObjectManager *>(get(sObjMan)), this);
#endif
}

/*!
\fn     void Engine::shutdown()
\brief  See Engine.h
*/
void Engine::shutdown(){
	
	//	Shutdown each system
	while(!shutdownStack.empty()){
	
		//	Shutdown the system
		shutdownStack.top() -> shutdown();
	
		//	Remove the system from the stack
		shutdownStack.pop();
	}
}

/*!
\fn     Engine::Engine()
\brief  See Engine.h
*/
Engine::Engine() : ISystem(sInvalid), isRunning(false){}

ISystem *Engine::get(ISystem::Type type){

	//	If the engine is running, `systems` is sorted, so use binary search
	if(isRunning) return binarySearch<ISystem, std::vector<ISystem *>, ISystem::Type>(systems, [](ISystem *sys, ISystem::Type type){
		return (int) sys -> getType() - (int) type;
	}, type);

	//	Otherwise, use sequential search
	else for(ISystem *system : systems) if(system -> getType() == type) return system;
	
	//	Return
	return nullptr;
}

/*!
\fn     void Engine::stop()
\brief  See Engine.h
*/
void Engine::stop(){
	isRunning = false;
}


/*!
\fn     Engine *Engine::getInstance()
\brief  See Engine.h
*/
Engine *Engine::getInstance(){

	//	Create singleton instance, if necessary
    if(instance == nullptr) instance = new Engine();

	//	Return
    return instance;
}

/*!
\fn     void Engine::closeInstance()
\brief  See Engine.h
*/
void Engine::closeInstance(){
	delete instance;
}

/*!
\var    instance
\brief  See Engine.h
*/
Engine *Engine::instance = nullptr;