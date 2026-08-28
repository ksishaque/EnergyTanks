/*!
\file BehaviorPowerUp.cpp
\author Khaled S. Ishaque
\date 11-9-2022
\brief
	CPP file for BehaviorPowerUp class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "BehaviorPlayer.h"
#include "BehaviorPowerUp.h"

//PowerUp variants
#include "GraphicsUnit.h"
#include "PowerUpRapidFire.h"
#include "PowerUpMoreBullets.h"
#include "PowerUpRapidSpeed.h"
#include "PowerUpBurst.h"
#include "PowerUpPierce.h"
#include "PowerUpStealthBullet.h"
#include "General.h"
#include "CollisionManager.h"
#include "Sprite.h"

#define DEBUG

BehaviorPowerUp::BehaviorPowerUp() :
	timer(0.0f),
	power(PowerUp::powerType::invalid),
	active(true)
{
}

BehaviorPowerUp::BehaviorPowerUp(const BehaviorPowerUp& other) :
	timer(other.timer),
	power(PowerUp::powerType::invalid),
	active(other.active)
{
}

BehaviorPowerUp::~BehaviorPowerUp()
{
	GameObject* gameobject = getParent();
	Sprite* sprite = dynamic_cast<Sprite*>(gameobject->get(ComponentTypeEnum::cSprite));
	GraphicsUnitMutable* gum = sprite->getGraphics(0);
	gum->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	//setPower(PowerUp::powerType::random);
	//CollisionManager::addToList(dynamic_cast<Collider*>(gameobject->get(ComponentTypeEnum::cCollider)));
	timer = 0.0f;
}
Component* BehaviorPowerUp::clone() const
{
	BehaviorPowerUp* clone = new BehaviorPowerUp();
	clone->timer = timer;
	clone->power = power;
	return clone;
}

void BehaviorPowerUp::update(float dt)
{

	/*
	GraphicsUnitMutable* gum = sprite->getGraphics(0);
	if (active)
	{
		active = false;
		//CollisionManager::removeFromList(dynamic_cast<Collider*>(gameobject->get(ComponentTypeEnum::cCollider)));
		gum->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.25f));
	}
	*/
	if (timer > 0) timer -= dt;
	else if (timer < 0)
	{
		GameObject* gameobject = getParent();
		Sprite* sprite = dynamic_cast<Sprite*>(gameobject->get(ComponentTypeEnum::cSprite));
		timer = 0;
		active = true;
		sprite->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		//setPower(PowerUp::powerType::random);
		//CollisionManager::addToList(dynamic_cast<Collider*>(gameobject->get(ComponentTypeEnum::cCollider)));
	}
}

/*!
 * @brief:
 * Sets the type of power up
 * @param:
 * power - The type of powerup that was gotten.
 * @return:
 * Nothing
 */
void BehaviorPowerUp::setPower(PowerUp::powerType powerType)
{
	power = powerType;
}

void BehaviorPowerUp::setDuration(float time)
{
	//power->resetDuration(time);
}

PowerUp* BehaviorPowerUp::getPower()
{
	if (timer > 0)
	{
		return nullptr;
	}
	PowerUp::powerType powerType = power;
	if (powerType == PowerUp::powerType::random)
	{
		powerType = static_cast<PowerUp::powerType>(randomInteger(7, 1));
	}
	PowerUp* pow;
	switch (powerType)
	{
	case PowerUp::powerType::rapidSpeed:
		pow = new RapidSpeed();
		break;
	case PowerUp::powerType::rapidFire:
		pow = new RapidFire();
		break;
	case PowerUp::powerType::moreBullets:
		pow = new MoreBullets(5, 2);
		break;
	case PowerUp::powerType::burst:
		pow = new Burst();
		break;
	case PowerUp::powerType::pierce:
		pow = new Pierce();
		break;
	case PowerUp::powerType::stealth:
		pow = new StealthBullet();
		break;
	default:
		pow = new PowerUp(PowerUp::powerType::invalid, PowerUp::powerCategory::cInvalid, 0.0f, 0);
		break;
	}
	timer += respawnTime;
	active = false;
	GameObject* gameobject = getParent();
	Sprite* sprite = dynamic_cast<Sprite*>(gameobject->get(ComponentTypeEnum::cSprite));
	sprite->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.25f));
	return pow;
}

void BehaviorPowerUp::setTimer(float time)
{
	//timer = time;
}
