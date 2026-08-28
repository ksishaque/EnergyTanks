/*****************************************************************//**
 * \file   ButtonAction.h
 * \brief  Header for ButtonAction.cpp
 * 
 * \author Luke Tseng
 * \date   October 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
#pragma once

#include <string>

#define BUTTON_ACTION_VOLUME_SCALE 3

/**
 * Restarts game
 *
 */
void restartGame();


/**
 * Shuts down game
 * 
 */
void shutdownGame();

void increaseMusicVolume(float dt);
void decreaseMusicVolume(float dt);
void increaseSfxVolume(float dt);
void decreaseSfxVolume(float dt);
void die(GameObject& obj);
void closeGame();

