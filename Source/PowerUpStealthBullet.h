/*!
\file PowerUpStealthBullet.h
\author Khaled S. Ishaque
\date 7-7-2023
\brief
	h file for StealthBullet class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/


#include "PowerUp.h"

class StealthBullet : public PowerUp {
public:
	StealthBullet(int ammo = 3);
	bool update(BehaviorPlayer& player, float dt);
	void shootEffect(BehaviorPlayer& player);
private:
	float newAlpha;
};