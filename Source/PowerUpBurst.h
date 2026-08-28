/*!
\file PowerUpBurst.h
\author Khaled S. Ishaque
\date 6-16-2023
\brief
    h file for Burst class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include "PowerUp.h"

class Burst : public PowerUp
{
public:
    Burst(int ammo = 6);
	bool update(BehaviorPlayer& player, float dt);
	void shootEffect(BehaviorPlayer& behavior);
private:
	float timer, timeToFire;
};