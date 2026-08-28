/*****************************************************************//**
 * \file   DebugSystem.cpp
 * \brief
 *
 * \author Luke
 * \date   November 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
#include <Windows.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Window.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "Renderer.h"
#include "GraphicsUnit.h"
#include "Trace.h"
#include "ObjectManager.h"
#include "DebugSystem.h"
#include "GameObject.h"
#include "ControlManager.h"
#include "DebugToggleAction.h"
#include "FunctionActionNode.h"
#include "DebugCloseAction.h"

#ifdef DEBUG_SYSTEM

DebugSystem::DebugSystem() : ISystem(sDebug), mesh(nullptr), texture(nullptr), history(DEBUG_SYSTEM_AVERAGE_SAMPLE_SIZE, 0.f), hotkeys()
{
    offset = glm::translate(glm::vec3(0, -45, 0));
    offsetFps = glm::translate(glm::vec3(-15, 0, 0));
	trans = glm::translate(glm::vec3(-625, 340, 1)) * glm::scale(glm::vec3(45, 45, 1));
    trans1 = glm::translate(glm::vec3(625, 340, 1)) * glm::scale(glm::vec3(30, 30, 1));
    trans2 = glm::translate(glm::vec3(625, 300, 1)) * glm::scale(glm::vec3(30, 30, 1));
    trans3 = glm::translate(glm::vec3(625, 260, 1)) * glm::scale(glm::vec3(30, 30, 1));
	setHotkeys();
}

void DebugSystem::initialize()
{
    texture = &TextureManager::getTexture("font");
    MeshManager::getInstance()->getMesh(MeshManager::MeshType::text, mesh);
	ControlManager *cont = ControlManager::getInstance();
	if (!cont->claimKey(GLFW_KEY_PAUSE))
	{
		Trace::error("Debug key (pause) could not be claimed");
	}
	cont->addAction(new DebugToggleAction(DEBUG_MAIN), GLFW_KEY_PAUSE, ControlManager::KeyState::PRESSED);
	cont->addAction(new DebugCloseAction(DEBUG_MAIN), GLFW_KEY_PAUSE, ControlManager::KeyState::RELEASED);
	if (!cont->claimKey(GLFW_KEY_BACKSPACE))
	{
		Trace::error("Debug key (pause) could not be claimed");
	}
	cont->addAction(new DebugToggleAction(DEBUG_MAIN), GLFW_KEY_BACKSPACE, ControlManager::KeyState::PRESSED);
	cont->addAction(new DebugCloseAction(DEBUG_MAIN), GLFW_KEY_BACKSPACE, ControlManager::KeyState::RELEASED);
}

static const char *FLAG_CHARS = "DCFLUS";

void DebugSystem::update(float& dt)
{
	if (dt > 0)
	{
		history.push_front(1 / dt);
		history.pop_back();
	}
    if (getFlag(DEBUG_MAIN))
    {
		glm::mat4 t = trans;
		if (!getFlag(HIDE_DEBUG)) {
			for (unsigned i = 0; i < (unsigned)DebugFlag::MAX; i += 1)
			{
				if(getFlag((DebugFlag)i))
				{
					Renderer::getInstance()->addToList(makeGraphicsUnit(mesh, t, GraphicsUnit::guDebug, texture, (float)FLAG_CHARS[i] / 96, 0, glm::vec4(1, 0, 0, 1)));
					t = offset * t;
				}
			}
		}
		if (!getFlag(HIDE_FPS))
		{
			int fps = (int)(history.front() + 0.5f);
			glm::mat4 tf = trans1;
			while (fps > 0)
			{
			    int digit = fps % 10;
			
				Renderer::getInstance()->addToList(makeGraphicsUnit(mesh, tf, GraphicsUnit::guDebug, texture, ((float)digit + 16) / 96, 0));
				fps /= 10;
				tf = offsetFps * tf;
			}
			float fpsAvg = 0;
			float fpsMin = -1;
			for (float past : history)
			{
				fpsAvg += past;
				if(fpsMin < 0 || past < fpsMin) fpsMin = past;
			}
			fpsAvg /= DEBUG_SYSTEM_AVERAGE_SAMPLE_SIZE;
			if (getFlag(SLOW_MOTION))
			{
				fpsAvg *= DEBUG_SYSTEM_SLOW_MOTION_RATIO;
			}
			fps = (int)(fpsAvg + 0.5f);
			tf = trans2;
			while (fps > 0)
			{
			    int digit = fps % 10;
		
			    Renderer::getInstance()->addToList(makeGraphicsUnit(mesh, tf, GraphicsUnit::guDebug, texture, ((float)digit + 16) / 96, 0));
			    fps /= 10;
			    tf = offsetFps * tf;
			}
			fps = (int)(fpsMin + 0.5f);
			tf = trans3;
			while (fps > 0)
			{
			    int digit = fps % 10;
		
			    Renderer::getInstance()->addToList(makeGraphicsUnit(mesh, tf, GraphicsUnit::guDebug, texture, ((float)digit + 16) / 96, 0));
			    fps /= 10;
			    tf = offsetFps * tf;
			}
		}
		if (getFlag(MANUAL_LAG))
		{
			Sleep(DEBUG_SYSTEM_LAG_TIME);
		}
		if (getFlag(SLOW_MOTION))
		{
			dt /= DEBUG_SYSTEM_SLOW_MOTION_RATIO;
		}
    }
	for (unsigned i = 0; i < (unsigned) DebugFlag::MAX; i += 1)
	{
		if (flags[i] > 1)
		{
			flags[i] -= dt;
		}
	}
}

DebugSystem *DebugSystem::instance = nullptr;

DebugSystem *DebugSystem::getInstance()
{
	if (instance == nullptr)
	{
		instance = new DebugSystem();
	}
	return instance;
}

void DebugSystem::closeInstance()
{
	delete instance;
	instance = nullptr;
}

void DebugSystem::toggleFlag(DebugFlag i)
{
	if (getFlag(i))
	{
		flags[i] = -1;
		if (i == DEBUG_MAIN)
		{
			for (DebugButton *hotkey : hotkeys)
			{
				hotkey->deactivate();
			}
		}
		return;
	}
	flags[i] = 1 + DEBUG_SYSTEM_HOLD_TIME;
	if (i == DEBUG_MAIN)
	{
		for (DebugButton *hotkey : hotkeys)
		{
			hotkey->activate();
		}
	}
}

DebugSystem::DebugButton::DebugButton(int key, const std::string &name) : active(false), key(key), name(name)
{
}

void DebugSystem::DebugButton::activate()
{
	active = ControlManager::getInstance()->claimKey(key);
	if (active)
	{
		addAction();
	}
	else
	{
		Trace::message("Debug hotkey \"%s\" could not be set", name);
	}
}

void DebugSystem::DebugPressButton::addAction()
{
	ControlManager::getInstance()->addAction(new FunctionActionNode<ActionFunctionVoid>(fn), key, ControlManager::KeyState::PRESSED);
}

DebugSystem::DebugPressButton::DebugPressButton(int key, void (*fn)(), const std::string &name) : DebugButton(key, name), fn(fn)
{
}

void DebugSystem::DebugButton::deactivate()
{
	if (active)
	{
		ControlManager::getInstance()->releaseKey(key);
	}
}

void DebugSystem::DebugHoldButton::addAction()
{
	ControlManager::getInstance()->addAction(new FunctionActionNode<ActionFunctionDt>(fn), key, ControlManager::KeyState::HELD);
}

DebugSystem::DebugHoldButton::DebugHoldButton(int key, void (*fn)(float), const std::string &name) : DebugButton(key, name), fn(fn)
{
}

void DebugSystem::shutdown()
{
	ControlManager::getInstance()->releaseKey(GLFW_KEY_PAUSE);
	if (getFlag(DEBUG_MAIN))
	{
		toggleFlag(DEBUG_MAIN);
	}
}

void DebugSystem::addHotkey(int key, void (*fn)(float), const std::string &name)
{
	hotkeys.push_back(new DebugHoldButton(key, fn, name));
}

void DebugSystem::addHotkey(int key, void (*fn)(), const std::string &name)
{
	hotkeys.push_back(new DebugPressButton(key, fn, name));
}

DebugSystem::~DebugSystem()
{
    for (DebugButton *hotkey : hotkeys)
	{
		delete hotkey;
	}
}

bool DebugSystem::getFlag(DebugFlag i)
{
	return flags[i] > 0;
}

void DebugSystem::closeFlag(DebugFlag i)
{
	if (!getFlag(i))
	{
		return;
	}
	flags[i] -= 1;
	if (i == DEBUG_MAIN && !getFlag(i))
	{
		for (DebugButton *hotkey : hotkeys)
		{
			hotkey->deactivate();
		}
	}
}

void DebugSystem::DebugFlagButton::addAction()
{
	ControlManager::getInstance()->addAction(new DebugToggleAction(flag), key, ControlManager::KeyState::PRESSED);
	ControlManager::getInstance()->addAction(new DebugCloseAction(flag), key, ControlManager::KeyState::RELEASED);
}

DebugSystem::DebugFlagButton::DebugFlagButton(int key, DebugFlag flag, const std::string &name) : DebugButton(key, name), flag(flag)
{
}

void DebugSystem::addHotkey(int key, DebugFlag flag, const std::string &name)
{
	hotkeys.push_back(new DebugFlagButton(key, flag, name));
}
#endif