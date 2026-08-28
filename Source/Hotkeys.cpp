/*!
\file   Hotkeys.cpp
\author Kevin Shin
\date   4-2-2023
\brief
        Functions for creating and managing debug hotkeys
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include <glfw/glfw3.h>

#include "Engine.h"
#include "ObjectManager.h"
#include "PopupObjectList.h"
#include "PauseSystem.h"
#include "Trace.h"
#include "DebugSystem.h"

#ifdef DEBUG_SYSTEM

//	Note: Some of the following functions will not have comments for convenience.
void debugGoToTitle(){
	ObjectManager::getInstance() -> changeState("Title");
}
void debugGoToSelect(){
	ObjectManager::getInstance() -> changeState("Select");
}
void debugGoToBattle1(){
	ObjectManager::getInstance() -> changeState("StartBattle");
}
void debugGoToBattle2(){
	ObjectManager::getInstance() -> changeState("StartBattle2");
}
void debugGoToBattle3(){
	ObjectManager::getInstance() -> changeState("StartBattle3");
}
void debugGoToBattle4(){
	ObjectManager::getInstance() -> changeState("StartBattle4");
}
void debugGoToWin1(){
	ObjectManager::getInstance() -> changeState("Win1");
}
void debugGoToWin2(){
	ObjectManager::getInstance() -> changeState("Win2");
}
void debugGoToWinTie(){
	ObjectManager::getInstance() -> changeState("WinTie");
}
void debugGoToSplash(){
	ObjectManager::getInstance() -> changeState("DigiPenSplash");
}
void debugReload(){
	ObjectManager::getInstance() -> changeState();
}
void debugClose(){
	Engine::getInstance() -> stop();
}
void debugLog(float dt){
	if(Trace::getInstance()->forceLog()) Trace::message("Trace log started from Debug Mode");
	else Trace::message("Debug Mode Ping [!@#]");
}
void debugSandbox(){
	//dynamic_cast<PopupObjectList *>(ObjectManager::getInstance()) -> addObject(nullptr);
}

void debugTutorial(){
	ObjectManager::getInstance() -> changeState("StartTutorial");
}


/*!
\fn     void DebugSystem::setHotkeys()
\brief  See DebugSystem.h
*/
void DebugSystem::setHotkeys(){

	//	Gamestate hotkeys
	addHotkey(GLFW_KEY_0, debugGoToTitle, "Title State");
	addHotkey(GLFW_KEY_1, debugGoToBattle1, "Battle1 State");
	addHotkey(GLFW_KEY_2, debugGoToBattle2, "Battle2 State");
	addHotkey(GLFW_KEY_3, debugGoToBattle3, "Battle3 State");
	addHotkey(GLFW_KEY_4, debugGoToBattle4, "Battle4 State");
	addHotkey(GLFW_KEY_5, debugGoToWin1, "Win1 State");
	addHotkey(GLFW_KEY_6, debugGoToWin2, "Win2 State");
	addHotkey(GLFW_KEY_7, debugGoToWinTie, "WinTie State");
	addHotkey(GLFW_KEY_8, debugGoToSplash, "Splash State");
	addHotkey(GLFW_KEY_9, debugGoToSelect, "Selection State");
	addHotkey(GLFW_KEY_MINUS, debugReload, "Reload");

	//	Debug flag hotkeys
	addHotkey(GLFW_KEY_PAGE_UP, DebugFlag::HIDE_UI, "UI");
	addHotkey(GLFW_KEY_PAGE_DOWN, DebugFlag::HIDE_FPS, "FPS");
	addHotkey(GLFW_KEY_HOME, DebugFlag::DRAW, "Debug Draw");
	/*
	addHotkey(GLFW_KEY_INSERT, DebugFlag::MANUAL_LAG, "Lag");
	/*/
	addHotkey(GLFW_KEY_INSERT, DebugFlag::HIDE_DEBUG, "Debug Flags");
	//*/
	addHotkey(GLFW_KEY_DELETE, DebugFlag::SLOW_MOTION, "SloMo");

	//	Miscellaneous hotkeys
	addHotkey(GLFW_KEY_ESCAPE, debugClose, "Shutdown");
	addHotkey(GLFW_KEY_END, debugLog, "Log");
	addHotkey(GLFW_KEY_EQUAL, debugSandbox, "Sandbox");

	addHotkey(GLFW_KEY_BACKSLASH, debugTutorial, "StartTutorial");

}

#endif