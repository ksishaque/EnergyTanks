/*****************************************************************//**
 * \file   CollisionResolution.cpp
 * \brief
 *
 * \author Luke Tseng
 * \date   October 2022
 * \par    Copyright © 2022 DigiPen, All rights reserved.
 *********************************************************************/
#define _USE_MATH_DEFINES
#include <cmath>
#include "CollisionResolution.h"
#include "TeamSystem.h"
#include "BehaviorButton.h"
#include "ParticleGenerator.h"
#include "SoundSystem.h"
#include "PowerUp.h"
#include "PowerUpMoreBullets.h"
#include "PowerUpRapidFire.h"
#include "PowerUpRapidSpeed.h"
#include "BehaviorPlayer.h"
#include "BehaviorBullet.h"


void death(GameObject* gameobject, glm::vec3& v)
{
    (void)v;
    gameobject->setDestroyed(true);
}

void caseDestroyOne(GameObject* obj)
{
    glm::vec3 nothing;
    death(obj, nothing);
}

void caseDestroyBoth(GameObject* obj1, GameObject* obj2)
{
    glm::vec3 nothing;
    death(obj1, nothing);
    death(obj2, nothing);
}

#include "Trace.h"
bool caseBounce(GameObject* obj, const BounceInfo& info)
{
	//check if there is a valid bounce
	if (!info.happen)
	{
		return false;
	}
	//get the transform and physics
	Transform* trans = dynamic_cast<Transform*>(obj->get(ComponentTypeEnum::cTransform));
	Physics* phys = dynamic_cast<Physics*>(obj->get(ComponentTypeEnum::cPhysics));
	if(trans == nullptr || phys == nullptr)
	{
		return false;
	}
	//save old endpoint
	glm::vec3 movCheck = trans->getTranslation();
	//get magnitude of movement
	glm::vec3 temp = phys->getVelocity();
	float speed = length(temp);
	//clear forces
	phys->clearForces();
	if (speed > 0)
	{

		//get angle of movement
		float angle = atan2f(temp.x, -temp.y);

		//update the translation
		temp = movCheck;
		temp += info.normal * info.distance;
		trans->setTranslation(temp);

		//update the old translation
		phys->setOldTrans(info.contact);

		//get reflection vector
		temp -= info.contact;

		//set new velocity
		if (temp.length() > 0)
		{
			temp = normalize(temp) * speed;
		}
		else
		{
			temp = reflect(phys->getVelocity(), info.normal);
		}
		phys->setVelocity(temp);
			
		//calculate difference in movement angles
		angle -= atan2f(temp.x, -temp.y);
		angle *= 180;
		angle /= (float)M_PI;

		//update rotation
		trans->setRotatePos(trans->getRotation() - angle);

	}

	//check for no velocity
	else if (info.contact != trans->getTranslation())
	{
		trans->setTranslation(info.contact);
	}
	return movCheck != trans->getTranslation();
}

bool slideOnLine(GameObject* obj, const BounceInfo& info)
{
	//check if there is a valid bounce
	if (!info.happen)
	{
		return false;
	}
	float distance = info.distance / 2;
	//get the transform and physics
	Transform* trans = dynamic_cast<Transform*>(obj->get(ComponentTypeEnum::cTransform));
	Physics* phys = dynamic_cast<Physics*>(obj->get(ComponentTypeEnum::cPhysics));
	if(trans == nullptr || phys == nullptr)
	{
		return false;
	}
	//save old endpoint
	glm::vec3 movCheck = trans->getTranslation();
	//get magnitude of movement
	glm::vec3 temp = phys->getVelocity();
	float speed = length(temp);
	//clear forces
	phys->clearForces();
	if (speed > 0)
	{

		//update the translation
		temp = movCheck;
		temp += info.normal * distance;
		trans->setTranslation(temp);

		//update the old translation
		phys->setOldTrans(info.contact);

	}

	//check for no velocity
	else if (info.contact != trans->getTranslation())
	{
		trans->setTranslation(info.contact);
	}
	return movCheck != trans->getTranslation();
}


// collision case checking - TODO: check if they all work, after json can start assigning types, teams and shields
void collisionCases(Collider* col1, bool& mov1, BounceInfo& info1, Collider* col2, bool& mov2, BounceInfo& info2, float dt)
{
    GameObject* g1 = col1->getParent();
    GameObject* g2 = col2->getParent();
    if (g1 && g2)
    {

        // Bullet and Shield - Destroys both and removes a shield from the team
        if (g1->getType() == GameObject::Bullet && g2->getType() == GameObject::Shield)
        {
            caseDestroyBoth(g1, g2);
			generateExplosion(g2, dt);
            SoundSystem::play("shieldDie", false);
			mov1 = false;
			mov2 = false;
            return;
        }
        if (g1->getType() == GameObject::Shield && g2->getType() == GameObject::Bullet)
        {
            caseDestroyBoth(g1, g2);
			generateExplosion(g1, dt);
            SoundSystem::play("shieldDie", false);
			mov1 = false;
			mov2 = false;
            return;
        }
        // Bullet and Player - Destroys both
        if (g1->getType() == GameObject::Player && g2->getType() == GameObject::Bullet)
        {
			if (TeamSystem::getInstance()->hasShields(g1->getTeam()))
			{
				//	Knockback
				caseKnockback(g1, info2);
				generateDefense(g1, g2, dt);
				SoundSystem::play("playerBlock", false);
			}
			else
			{
				caseDestroyOne(g1);
				generateExplosion(g1, dt);
				SoundSystem::play("playerDie", false);
			}
            caseDestroyOne(g2);
			mov1 = false;
			mov2 = false;
            return;
        }
        if (g1->getType() == GameObject::Bullet && g2->getType() == GameObject::Player && !TeamSystem::getInstance()->hasShields(g2->getTeam()))
        {
			if (TeamSystem::getInstance()->hasShields(g2->getTeam()))
			{
				//	Knockback
				caseKnockback(g2, info1);
				generateDefense(g2, g1, dt);
				SoundSystem::play("playerBlock", false);
			}
			else
			{
				caseDestroyOne(g2);
				generateExplosion(g2, dt);
				SoundSystem::play("playerDie", false);
			}
            caseDestroyOne(g1);
			mov1 = false;
			mov2 = false;
            return;
        }
        // Bullet and Button 
        if (g1->getType() == GameObject::Bullet && g2->getType() == GameObject::Button)
        {
            Behavior* button = dynamic_cast<Behavior*>(g2->get(ComponentTypeEnum::cBehavior));
            BehaviorButton* button2 = dynamic_cast<BehaviorButton*>(button);
            button2->activate(g1->getTeam());
            g1->setDestroyed(true);
			//SoundSystem::play("uiConfirm", false);
			mov1 = false;
			mov2 = false;
            return;
        }
        if (g1->getType() == GameObject::Button && g2->getType() == GameObject::Bullet)
        {
            Behavior* button = dynamic_cast<Behavior*>(g1->get(ComponentTypeEnum::cBehavior));
            BehaviorButton* button2 = dynamic_cast<BehaviorButton*>(button);
            button2->activate(g2->getTeam());
            g2->setDestroyed(true);
			//SoundSystem::play("uiConfirm", false);
			mov1 = false;
			mov2 = false;
            return;
        }
        // Bullet and Wall - Bullet bounces off walls
        if (g1->getType() == GameObject::Bullet && g2->getType() == GameObject::Wall)
        {
            Behavior* bullet = dynamic_cast<Behavior*>(g1->get(ComponentTypeEnum::cBehavior));
            BehaviorBullet* bullet2 = dynamic_cast<BehaviorBullet*>(bullet);
			if (bullet2->doPierce() == true) {
				return;
			}
			mov1 = caseBounce(g1, info1);
			mov2 = false;
			if(mov1)
			{
				generateSpark(g1, dt);
				SoundSystem::play("bulletWall", false);
				bullet2->hitTimer();
			}
            return;
        }
        if (g1->getType() == GameObject::Wall && g2->getType() == GameObject::Bullet)
        {
            Behavior* bullet = dynamic_cast<Behavior*>(g2->get(ComponentTypeEnum::cBehavior));
            BehaviorBullet* bullet2 = dynamic_cast<BehaviorBullet*>(bullet);
			if (bullet2->doPierce() == true) {
				return;
			}
			mov1 = false;
			mov2 = caseBounce(g2, info2);
			if(mov2){
				generateSpark(g2, dt);
				SoundSystem::play("bulletWall", false);
				bullet2->hitTimer();
			}
            return;
        }
        // Player and Wall - Player bounces off walls
        if (g1->getType() == GameObject::Player && g2->getType() == GameObject::Wall)
        {
#ifdef TANKBOUNCE
			mov1 = caseBounce(g1, info1);
#else
			mov1 = slideOnLine(g1, info1);
#endif
			mov2 = false;
			if(mov1) SoundSystem::play("playerWall", false);
            return;
        }
        if (g1->getType() == GameObject::Wall && g2->getType() == GameObject::Player)
        {
#ifdef TANKBOUNCE
			mov2 = caseBounce(g2, info2);
#else
			mov2 = slideOnLine(g2, info2);
#endif
			mov1 = false;
			if(mov2) SoundSystem::play("playerWall", false);
            return;
        }
        // Bullet and Map - Bullet bounces off edges
        if (g1->getType() == GameObject::Bullet && g2->getType() == GameObject::Map)
        {
            Behavior* bullet = dynamic_cast<Behavior*>(g1->get(ComponentTypeEnum::cBehavior));
            BehaviorBullet* bullet2 = dynamic_cast<BehaviorBullet*>(bullet);
			if (bullet2->doPierce() == true) {
				return;
			}
			mov1 = caseBounce(g1, info1);
			mov2 = false;
			if(mov1){
				generateSpark(g1, dt);
				SoundSystem::play("bulletWall", false);
				bullet2->hitTimer();
			}
            return;
        }
        if (g1->getType() == GameObject::Map && g2->getType() == GameObject::Bullet)
        {
            Behavior* bullet = dynamic_cast<Behavior*>(g2->get(ComponentTypeEnum::cBehavior));
            BehaviorBullet* bullet2 = dynamic_cast<BehaviorBullet*>(bullet);
			if (bullet2->doPierce() == true) {
				return;
			}
			mov1 = false;
			mov2 = caseBounce(g2, info2);
			if(mov2){
				generateSpark(g2, dt);
				SoundSystem::play("bulletWall", false);
				bullet2->hitTimer();
			}
            return;
        }
        // Player and Map - Player bounces off edges
        if (g1->getType() == GameObject::Player && g2->getType() == GameObject::Map)
        {
#ifdef TANKBOUNCE
			mov1 = caseBounce(g1, info1);
#else
			mov1 = slideOnLine(g1, info1);
#endif
			mov2 = false;
			if(mov1) SoundSystem::play("playerWall", false);
            return;
        }
        if (g1->getType() == GameObject::Map && g2->getType() == GameObject::Player)
        {
#ifdef TANKBOUNCE
			mov2 = caseBounce(g2, info2);
#else
			mov2 = slideOnLine(g2, info2);
#endif
			mov1 = false;
			if(mov2) SoundSystem::play("playerWall", false);
            return;
        }
        // Player and Player - Players bounce off each other
        if (g1->getType() == GameObject::Player && g2->getType() == GameObject::Player)
        {
#ifndef TANKBOUNCE
			info1.distance /= 1.999f;
			info2.distance /= 1.999f;
#endif

			mov1 = caseBounce(g1, info1);
			mov1 = caseBounce(g2, info2);
			if(mov1 || mov2) SoundSystem::play("playerWall", false);
            return;
        }
        // Bullet and Bullet - Bullets bounce off each other
        if (g1->getType() == GameObject::Bullet && g2->getType() == GameObject::Bullet)
        {
            Behavior* bullet = dynamic_cast<Behavior*>(g1->get(ComponentTypeEnum::cBehavior));
            BehaviorBullet* bullet2 = dynamic_cast<BehaviorBullet*>(bullet);
            bullet = dynamic_cast<Behavior*>(g2->get(ComponentTypeEnum::cBehavior));
            bullet2 = dynamic_cast<BehaviorBullet*>(bullet);
			mov1 = caseBounce(g1, info1);
			mov2 = caseBounce(g2, info2);
			if(mov1 || mov2) SoundSystem::play("bulletBullet", false);
            return;
        }
        // Player picks up powerup
        if (g1->getType() == GameObject::Player && g2->getType() == GameObject::Powerup)
        {
            BehaviorPlayer* player = dynamic_cast<BehaviorPlayer*>(g1->get(ComponentTypeEnum::cBehavior));
			BehaviorPowerUp* powerup = dynamic_cast<BehaviorPowerUp*>(g2->get(ComponentTypeEnum::cBehavior));
			PowerUp* power = powerup->getPower();
			player->setPowerUp(power);
			//powerup->setTimer(powerup->respawnTime);
			if (power)
			{
				SoundSystem::play("powerGet", false);
			}
			mov1 = false;
			mov2 = false;
            return;
        }
        if (g1->getType() == GameObject::Powerup && g2->getType() == GameObject::Player)
        {
            BehaviorPlayer* player = dynamic_cast<BehaviorPlayer*>(g2->get(ComponentTypeEnum::cBehavior));
			BehaviorPowerUp* powerup = dynamic_cast<BehaviorPowerUp*>(g1->get(ComponentTypeEnum::cBehavior));
			PowerUp* power = powerup->getPower();
			player->setPowerUp(power);
			//powerup->setTimer(powerup->respawnTime);
			if (power)
			{
				SoundSystem::play("powerGet", false);
			}
			mov1 = false;
			mov2 = false;
            return;
        }
    }
    return;
}


bool oppositeTeams(GameObject* obj1, GameObject* obj2)
{
    return obj1->getTeam() == -(obj2->getTeam());
}

/*!
\fn     void generateExplosion(GameObject* obj, float dt)
\brief  See CollisionResolution.h
*/
void generateExplosion(GameObject* obj, float dt) {
	ParticleGenerator* particleGenerator = ParticleGenerator::getInstance();
	particleGenerator->spawnParticles(obj, Particle::Explosion);
}

/*!
\fn     void generateSpark(GameObject* obj, float dt)
\brief  See CollisionResolution.h
*/
void generateSpark(GameObject* obj, float dt) {
	ParticleGenerator* particleGenerator = ParticleGenerator::getInstance();
	particleGenerator->spawnParticles(obj, Particle::BounceSparks);
}

/*!
\fn     void generateDefense(GameObject* obj1, GameObject* obj2, float dt)
\brief  See CollisionResolution.h
*/
void generateDefense(GameObject* obj1, GameObject* obj2, float dt) {
	ParticleGenerator* particleGenerator = ParticleGenerator::getInstance();
	particleGenerator->spawnParticles(obj1, Particle::Defense);
	particleGenerator->spawnParticles(obj2, Particle::BounceSparks);
}

void caseKnockback(GameObject* obj, const BounceInfo& info)
{
	Physics* phys = dynamic_cast<Physics*>(obj->get(ComponentTypeEnum::cPhysics));
	if(phys && info.happen)
	{
		phys->addForce(info.normal * -1.f);
	}
}