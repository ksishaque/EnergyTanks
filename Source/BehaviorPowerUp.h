/*!
\file BehaviorPowerUp.h
\author Khaled S. Ishaque
\date 11-9-2022
\brief
    h file for BehaviorPowerUp class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include "Behavior.h"
#include "PowerUp.h"

class BehaviorPowerUp : public Behavior
{
public:
	float respawnTime = 7.0f;

    BehaviorPowerUp();
    BehaviorPowerUp(const BehaviorPowerUp& other);
	~BehaviorPowerUp();
    Component* clone() const;
    void update(float dt);
    void setPower(PowerUp::powerType powerType);
	void setDuration(float time);
    PowerUp* getPower();
	void setTimer(float time);
private:
    float timer;
    PowerUp::powerType power;
	bool active;
};