/*!
\file BehaviorHealth.cpp
\author Khaled S. Ishaque
\date 1-27-2022
\brief
	CPP file for BehaviorHealth class and functions in class.
		("health" means the 1 bar and # of shields online for player)
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "GraphicsUnit.h"
#include "MeshManager.h"
#include "Sprite.h"
#include "TeamSystem.h"
#include "Transform.h"
#include "BehaviorHealth.h"

//how to shield count
//TeamSystem::getInstance() -> getShieldCount(getParent()->getTeam())

/*!
 * @brief:
 * Constructor for the BehaviorHealth Class
 * @param:
 * timeframe - time for shield bar to regenerate
 * @return:
 * Nothing
 */
BehaviorHealth::BehaviorHealth(float timeframe) :
	shieldNumber(-4),
	regenTime(timeframe),
	isDisplayed(false) {

}

/*!
 * @brief:
 * Copy Ctor for BehaviorHealth class
 * @param:
 * base - BehaviorHealth to copy from
 * @return:
 * Nothing
 */
BehaviorHealth::BehaviorHealth(const BehaviorHealth& base) : 
shieldNumber(base.shieldNumber),
regenTime(base.regenTime),
isDisplayed(false) {

}

/*!
 * @brief:
 * get the current number of shields active
 * @return:
 * number of shields
 */
unsigned int BehaviorHealth::getShield() {
	return shieldNumber;
}

/*!
 * @brief:
 * Set the timer for the new regen time
 * @param:
 * timeframe - the new timeframe to make
 */
void BehaviorHealth::setTimer(float timeframe) {
	regenTime = timeframe;
}

/*!
 * @brief:
 * Set the number of active shields
 * @param:
 * sNum - new shield number to set
 */
void BehaviorHealth::setShieldNum(int sNum) {
	shieldNumber = sNum;
}

/*!
 * @brief:
 * Set the textrue of the health object
 * @param:
 * text - the new texture to set
 */
//void BehaviorHealth::setTexture(Texture& text) {
//	texture = &text;
//}

/*!
 * @brief:
 * updates the health objects' behavior
 * @param:
 * dt - delta time (time frame changed)
 */
void BehaviorHealth::update(float dt) {
	//get the parent game object
	GameObject* parent = getParent();
	if (parent == nullptr) {
		return;
	}
	//get the sprite of the object
	Sprite* sprited = dynamic_cast<Sprite*>(parent->get(ComponentTypeEnum::cSprite));
	if (sprited == nullptr) {
		return;
	}
	//if the shield number is different from what is already the max
	if ((shieldNumber > 0 && TeamSystem::getInstance()->getShieldCount(parent->getTeam()) >= shieldNumber) || (shieldNumber == 0 && TeamSystem::getInstance()->getPlayer(getParent()->getTeam()))) {
		//check if it's being displayed
		/*
		if (!isDisplayed) {
			//Try to set the mesh of the object and display it
			Mesh* mesh;
			if (!MeshManager::getInstance()->getMesh(MeshManager::MeshType::single, mesh)) {
				return;
			}
			sprited->addToGraphics(new GraphicsUnitMutable(mesh, nullptr, GraphicsUnit::Type::guUI, texture, 0, 0));
			isDisplayed = true;
		}
		*/

	}
	//clear the texture graphics and set the display to false
	else// if (isDisplayed) {
	{
		sprited->clearGraphics();
		isDisplayed = false;
		getParent()->setDestroyed();

	}
}

/*!
 * @brief:
 * clone function for health component
 * @return:
 * cloned version of the health behavior
 */
Component* BehaviorHealth::clone() const {
	BehaviorHealth* nbHealth = new BehaviorHealth(*this);
	return nbHealth;
}