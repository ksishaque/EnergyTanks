/*!
\file BehaviorBullet.cpp
\author Khaled S. Ishaque
\date 10-11-2022
\brief
    CPP file for BehaviorBullet class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "GameObject.h"
#include "ParticleGenerator.h"
#include "TeamSystem.h"

#include "BehaviorBullet.h"

/*!
 * @brief:
 * Default Constructor for BehaviorBullet class
 * @param:
 * None
 * @return:
 * Nothing
 */
BehaviorBullet::BehaviorBullet(bool pierce, float timer) :
	timer(timer),
	teamSet(false),
	piercing(pierce),
	trail(true),
	trailParticleTimer(0.0f)
{
}

/*!
 * @brief:
 * Copy Constructor for BehaviorBullet class
 * @param:
 * bulletBehavior - The behavior to copy over
 * @return:
 * Nothing
 */
BehaviorBullet::BehaviorBullet(const BehaviorBullet& bulletBehavior) :
	timer(bulletBehavior.timer),
	teamSet(bulletBehavior.teamSet),
	piercing(bulletBehavior.piercing),
	trail(bulletBehavior.trail),
	trailParticleTimer(bulletBehavior.trailParticleTimer)
{
}

/*!
 * @brief:
 * Default Destructor for BehaviorBullet class
 * @param:
 * None
 * @return:
 * Nothing
 */
BehaviorBullet::~BehaviorBullet()
{
}

/*!
 * @brief:
 * Updates the timer for the BehaviorBullet class
 * @param:
 * dt - The change in time
 * @return:
 * Nothing
 */
void BehaviorBullet::update(float dt)
{
	/*
	if (!teamSet) {
		//	Variable: parent of the behavior
		GameObject* parent = getParent();

		//	Check `parent`
		if (parent) {

			//	Add player to `parent`'s team
			teamSet = TeamSystem::getInstance()->incPlayers(parent->getTeam());

		}

	}
	*/

    if (timer > 0)
    {
        timer -= dt;
		// generate bullet trail tracks
		if (trail) { generateBulletTrail(dt); }
    }
    else
    {
		GameObject* bullet = this->getParent();
		if(bullet)
		{
			bullet->setDestroyed(true);
		}
    }
}

/*!
 * @brief:
 * Component Cloner for BehaviorBullet class
 * @param:
 * None
 * @return:
 * Nothing
 */
Component* BehaviorBullet::clone() const
{
    BehaviorBullet* clone = new BehaviorBullet();
    clone->timer = timer;
    return clone;
}

/*!
 * @brief:
 * Sets the timer for the bullet's behavior
 * @param:
 * timer - The new time to set the bullet's timer to
 * @return:
 * Nothing
 */
void BehaviorBullet::setTimer(float timer)
{
	this->timer = timer;
}

/*!
 * @brief:
 * Reduces the timer for the bullet's behavior by a set amount
 * @param:
 * none
 * @return:
 * Nothing
 */
void BehaviorBullet::hitTimer()
{
	timer -= BULLET_BOUNCE_TIMER_HIT;
}

/*!
\fn     void generateBulletTrail(float dt)
\param  dt
			Time since previous frame
\return Nothing
\brief
		This funcion generates bullet trail particles every `trailParticleTimer` timeout.
*/
void BehaviorBullet::generateBulletTrail(float dt) {
	/*|BENEDICT|*/
	if (trailParticleTimer < 0.0f)
	{
		// Reset timer and generate particle.
		while (trailParticleTimer < 0) trailParticleTimer += 0.0625f;
		ParticleGenerator* particleGenerator = ParticleGenerator::getInstance();

		GameObject* gameObject = getParent();
		if (gameObject) {
			particleGenerator->spawnParticles(gameObject, Particle::BulletTrail);
		}

	}
	trailParticleTimer -= dt;
}

void BehaviorBullet::setPierce(bool p) {
	piercing = p;
}

bool BehaviorBullet::doPierce() {
	return piercing;
}

void BehaviorBullet::doTrailing(bool t) {
	trail = t;
}