/*****************************************************************//**
 * \file   ButtonAction.cpp
 * \brief  Different actions for the button when pressed
 * 
 * \author Luke Tseng
 * \date   October 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/

#include "Trace.h"
#include "Engine.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "ShutdownSystem.h"
#include "SoundSystem.h"
#include "ButtonAction.h"

void restartGame()
{
    //Trace::message("RESTART");
	ObjectManager::getInstance()->changeState();
}

void shutdownGame()
{
    ShutdownSystem::getInstance()->initiateShutdown();
}

void increaseMusicVolume(float dt)
{
	float dv = dt / BUTTON_ACTION_VOLUME_SCALE;
	float volume = SoundSystem::getInstance()->getMusicVolume();
	if(volume > 1 - dv) volume = 1;
	else volume += dv;
	SoundSystem::setMusicVolume(volume);
}

void decreaseMusicVolume(float dt)
{
	float dv = dt / BUTTON_ACTION_VOLUME_SCALE;
 	float volume = SoundSystem::getInstance()->getMusicVolume();
	if (volume < dv) volume = 0;
	else volume -= dv;
	SoundSystem::setMusicVolume(volume);
}
void increaseSfxVolume(float dt)
{
	float dv = dt / BUTTON_ACTION_VOLUME_SCALE;
	float volume = SoundSystem::getInstance()->getSfxVolume();
	if (volume > 1 - dv) volume = 1;
	else volume += dv;
	SoundSystem::setSfxVolume(volume);
}

void decreaseSfxVolume(float dt)
{
	float dv = dt / BUTTON_ACTION_VOLUME_SCALE;
	float volume = SoundSystem::getInstance()->getSfxVolume();
	if (volume < dv) volume = 0;
	else volume -= dv;
	SoundSystem::setSfxVolume(volume);
}

void die(GameObject &obj)
{
	obj.setDestroyed();
}

void closeGame()
{
    Engine::getInstance()->stop();
}