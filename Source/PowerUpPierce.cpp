/*!
\file PowerUpPierce.cpp
\author Khaled S. Ishaque
\date 6-30-2022
\brief
	CPP file for Pierce class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include <stdio.h>

#include "BehaviorPlayer.h"
#include "PowerUpPierce.h"
#include "Trace.h"

Pierce::Pierce(int ammo) : PowerUp(PowerUp::pierce, PowerUp::cAmmo, 0.0f, ammo),
	pierce(false)
{

}

void Pierce::shootEffect(BehaviorPlayer& player) {
	pierce = true;
	player.spawnBullet(0, pierce);
	decreaseAmmo();
}

bool Pierce::update(BehaviorPlayer& player, float dt) {
	return PowerUp::update(player, dt);
}