/*!
\file PowerUpPierce.h
\author Khaled S. Ishaque
\date 6-30-2023
\brief
	h file for Pierce class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include "PowerUp.h"

class Pierce : public PowerUp {
public:
	Pierce(int ammo = 3);
	bool update(BehaviorPlayer& player, float dt);
	void shootEffect(BehaviorPlayer& player);

private:
	bool pierce;
};