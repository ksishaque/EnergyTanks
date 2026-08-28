/*!
\file   Tank Game.cpp
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   9-9-2022
\brief
        Functions for managing a sprite
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include <Windows.h>
#include <glfw/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "CollisionManager.h"
#include "ControlManager.h"
#include "DebugSystem.h"
#include "Engine.h"
#include "MeshManager.h"
#include "ObjectCuller.h"
#include "ObjectManager.h"
#include "ParticleGenerator.h"
#include "PauseSystem.h"
#include "Renderer.h"
#include "ShaderManager.h"
#include "ShutdownSystem.h"
#include "SoundSystem.h"
#include "TeamSystem.h"
#include "TextureManager.h"
#include "Trace.h"
#include "Window.h"

#ifdef _DEBUG
/*!
\fn     void debugBreak(const ObjectManager *man, const Engine *eng)
\param  man
          Object manager, pulled forward for convenience
\param  eng
          Engine, pulled forward so it can be checked
\return Nothing
\brief
        This function provides a quick location for a breakpoint while in debug mode.
*/
void debugBreak(const ObjectManager *man, const Engine *eng){
	;
}
#endif

int WINAPI wWinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prevInstance, _In_ PWSTR pCmdLine, _In_ int cmdShow){
    Engine &engine = *Engine::getInstance();
	
#ifdef DEBUG_SYSTEM
	engine.addSystem(Trace::getInstance());
#endif
    engine.addSystem(Window::getInstance());
    engine.addSystem(ShaderManager::getInstance());
    engine.addSystem(TextureManager::getInstance());
    engine.addSystem(Renderer::getInstance());
    engine.addSystem(MeshManager::getInstance());
    engine.addSystem(SoundSystem::getInstance());
    engine.addSystem(CollisionManager::getInstance());
    engine.addSystem(ObjectManager::getInstance("DigiPenSplash"));
	engine.addSystem(PauseSystem::getInstance());
	engine.addSystem(ShutdownSystem::getInstance());
    engine.addSystem(ParticleGenerator::getInstance());
    engine.addSystem(TeamSystem::getInstance());
	engine.addSystem(ControlManager::getInstance());
#ifdef DEBUG_SYSTEM
    engine.addSystem(DebugSystem::getInstance());
#endif

	//	Variable: culler for `objMan`
    ObjectCuller culler(*ObjectManager::getInstance());

	//	Add `objMan` and `culler` to the engine
    engine.addSystem(&culler);

	//	Run `engine`
	try{
		engine.initialize();
	}
#ifdef DEBUG_SYSTEM
	catch(const std::exception& err){

		//	Trace the error
		Trace::error(err.what());

		//	Return;
		return 1;

	}
	catch(const std::string& err){

		//	Trace the error
		Trace::error(err.c_str());

		//	Return;
		return 1;

	}
#endif
	catch(...){
		return 1;
	}

	//	Close Singleton instances
#ifdef DEBUG_SYSTEM
	Trace::closeInstance();
#endif
	Window::closeInstance();
    ShaderManager::closeInstance();
	TextureManager::closeInstance();
	Renderer::closeInstance();
	MeshManager::closeInstance();
	SoundSystem::closeInstance();
	CollisionManager::closeInstance();
	ShutdownSystem::closeInstance();
	PauseSystem::closeInstance();
	ObjectManager::closeInstance();
    ParticleGenerator::closeInstance();
    TeamSystem::closeInstance();
	ControlManager::closeInstance();
#ifdef DEBUG_SYSTEM
    DebugSystem::closeInstance();
#endif

	Engine::closeInstance();

	//	Return
	return 0;

}