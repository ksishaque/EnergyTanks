/*!
\file PowerUpStealthBullet.cpp
\author Khaled S. Ishaque
\date 7-7-2023
\brief
	cpp file for StealthBullet class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "PowerUpStealthBullet.h"
#include "BehaviorPlayer.h"

StealthBullet::StealthBullet(int ammo) : 
	PowerUp(PowerUp::powerType::stealth, PowerUp::powerCategory::cAmmo, 0.0f, ammo),
	newAlpha(0.0f)
{

}

void StealthBullet::shootEffect(BehaviorPlayer& player) {
	newAlpha = 0.2f;
	player.spawnBullet(0, false, newAlpha);
	decreaseAmmo();
}

bool StealthBullet::update(BehaviorPlayer& player, float dt) {
	return PowerUp::update(player, dt);
}