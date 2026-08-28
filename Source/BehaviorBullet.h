/*!
\file BehaviorBullet.h
\author Khaled S. Ishaque
\date 10-11-2022
\brief
    H file for BehaviorBullet class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include  "Behavior.h"
#include <glm/glm.hpp>

#define BULLET_BOUNCE_TIMER_HIT 1

class BehaviorBullet : public Behavior
{
private:
    float timer;
public:
    BehaviorBullet(bool pierce = false, float timer = 5.0f);
    BehaviorBullet(const BehaviorBullet& bulletBehavior);
    ~BehaviorBullet();
    void update(float dt);
	void setTimer(float timer);
	void hitTimer();
	void setPierce(bool p);
	bool doPierce();
	void doTrailing(bool t);
    Component* clone() const override;
private:

	/*!
	\var    teamSet
				If the team of the player has been updated
	*/
	bool teamSet;

	/*!
	\var    trailParticleTimer
				Timer for making the particle bullet trail
	*/
	float trailParticleTimer;

	bool piercing;

	bool trail;

	/*!
	\fn     void generateBulletTrail(float dt)
	\param  dt
				Time since previous frame
	\return Nothing
	\brief
			This funcion generates bullet trail particles every `trailParticleTimer` timeout.
	*/

	void generateBulletTrail(float dt);
};