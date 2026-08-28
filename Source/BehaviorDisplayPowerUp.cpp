/*!
\file   BehaviorDisplayPowerUp.cpp
\author Khaled Ishaque
\author Kevin Shin
\date   4-10-2023
\brief
        Functions for managing the behavior of a display mode signifier
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "TeamSystem.h"
#include "GameObject.h"
#include "GraphicsUnit.h"
#include "Sprite.h"
#include "BehaviorPlayer.h"

#include "BehaviorDisplayPowerUp.h"

#ifdef NEW_PU_DISPLAY

/*!
 * @brief:
 * Constructor for the BehaviorDisplayPowerUp Class
 * @param:
 * None
 * @return:
 * Nothing
 */
BehaviorDisplayPowerUp::BehaviorDisplayPowerUp() :
	Behavior(),
	key(1)
{
}

/*!
 * @brief:
 * Copy Constructor for the BehaviorDisplayPowerUp Class
 * @param:
 * None
 * @return:
 * Nothing
 */
BehaviorDisplayPowerUp::BehaviorDisplayPowerUp(const BehaviorDisplayPowerUp &that) : 
	Behavior(),
	key(1)
{
}

/*!
 * @brief:
 * update the behavior of the power up display
 * @param:
 * dt - calculated time passed per frame
 * @return:
 * Nothing
 */
void BehaviorDisplayPowerUp::update(float dt) {

	//get the parent game object
	GameObject* obj = getParent();

	//null check
	if (obj == nullptr) { return; }

	//get the object's sprite
	Sprite *spr = dynamic_cast<Sprite*>(obj->get(ComponentTypeEnum::cSprite));

	//null check
	if (spr == nullptr) { return; }

	//get the player of the team
	BehaviorPlayer* player = dynamic_cast<BehaviorPlayer*>(TeamSystem::getInstance()->getPlayer(getParent()->getTeam()));

	//get the powerup type
	int pow = 0;
	if (player->activePowerUp()) {
		pow = player->getPowerUp()->getType();
	}
	pow += 1;

	//if the team changed the powerup, display
	if (pow != key) {

		//remove current display
		GraphicsUnitMutable* gu = spr -> getGraphics(key);
		if(gu != nullptr) {
			gu -> setColor({0.0f, 0.0f, 0.0f, 0.0f});
		}

		//display new powerup
		gu = spr -> getGraphics(pow);
		if(gu != nullptr) {
			gu -> setColor({1.0f, 1.0f, 1.0f, 1.0f});
		}

		//remember current key
		key = pow;
	}
}

/*!
 * @brief:
 * clone a BehaviorDisplayPowerUp class
 * @param:
 * None
 * @return:
 * a copy of the behavior it was meant to clone
 */
BehaviorDisplayPowerUp *BehaviorDisplayPowerUp::clone() const {
	return new BehaviorDisplayPowerUp();
}

#else

/*!
 * @brief:
 * Constructor for the BehaviorDisplayPowerUp Class
 * @param:
 * None
 * @return:
 * Nothing
 */
BehaviorDisplayPowerUp::BehaviorDisplayPowerUp() :
	Behavior(),
	fullColor(1, 1, 1, 1),
	dColor(1, 1, 1, 0),
	key(-1)
{
}

/*!
 * @brief:
 * Copy Constructor for the BehaviorDisplayPowerUp Class
 * @param:
 * None
 * @return:
 * Nothing
 */
BehaviorDisplayPowerUp::BehaviorDisplayPowerUp(const BehaviorDisplayPowerUp &that) : 
	Behavior(), 
	fullColor(that.fullColor), 
	dColor(that.dColor),
	key(that.key)
{
}

/*!
 * @brief:
 * update the behavior of the power up display
 * @param:
 * dt - calculated time passed per frame
 * @return:
 * Nothing
 */
void BehaviorDisplayPowerUp::update(float dt) {

	//get the parent game object
	GameObject* obj = getParent();

	//null check
	if (obj == nullptr) { return; }

	//get the object's sprite
	Sprite *spr = dynamic_cast<Sprite*>(obj->get(ComponentTypeEnum::cSprite));

	//null check
	if (spr == nullptr) { return; }

	//get the player of the team
	BehaviorPlayer* player = dynamic_cast<BehaviorPlayer*>(TeamSystem::getInstance()->getPlayer(getParent()->getTeam()));

	//if the team collected the powerup, display
	if (player->activePowerUp()) {
		PowerUp* pow = player->getPowerUp();
		if (pow->getType() == key) {
			spr->setColor(fullColor);
		}
		else {
			spr->setColor(dColor);
		}
	}
	else {
		spr->setColor(dColor);
	}

}

/*!
 * @brief:
 * clone a BehaviorDisplayPowerUp class
 * @param:
 * None
 * @return:
 * a copy of the behavior it was meant to clone
 */
BehaviorDisplayPowerUp *BehaviorDisplayPowerUp::clone() const {
	return new BehaviorDisplayPowerUp(*this);
}

/*!
 * @brief:
 * set the color of the display when active
 * @param:
 * full - the vector containing the values to set the color vector
 * @return:
 * Nothing
 */
void BehaviorDisplayPowerUp::setPowerUpColor(const glm::vec4 &full) {
	fullColor = full;
}

/*!
 * @brief:
 * set the color of the display when inactive
 * @param:
 * d - the vector containing the values to set the color vector
 * @return:
 * Nothing
 */
void BehaviorDisplayPowerUp::setDeadColor(const glm::vec4 &d) {
	dColor = d;
}


void BehaviorDisplayPowerUp::setKey(const int k) {
	key = k;
}

#endif