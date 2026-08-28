/*!
\file PowerUpBurst.cpp
\author Khaled S. Ishaque
\date 6-16-2022
\brief
	CPP file for Burst class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#include <stdio.h>

#include "BehaviorPlayer.h"
#include "PowerUpBurst.h"
#include "Trace.h"

Burst::Burst(int ammo) :
	PowerUp(PowerUp::burst, PowerUp::cAmmo, 0.0f, ammo),
	timer(-1),
	timeToFire(0)
{
#ifdef DEBUG_SYSTEM
    Trace::message("Burst Bullet Ctor Made.");
#endif
}

bool Burst::update(BehaviorPlayer& player, float dt) {
	if (timer >= 0) {
		//timer is active
		//next frame
		timer = timer - dt;
		//check if the timer altered with the frame has pass the timer mark
		if (timer < timeToFire) {
			//decrement timer and fire
			timeToFire -= 0.1f;
			player.spawnBullet(0);
			decreaseAmmo();
		}
	}

	return PowerUp::update(player, dt);
	//return false;
}


void Burst::shootEffect(BehaviorPlayer& player) {
	if (timer < 0) {
		//make timer
		timeToFire = 0.1f;
		timer = timeToFire * 2;
		//
	}
}