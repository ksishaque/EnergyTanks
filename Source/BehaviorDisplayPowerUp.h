/*!
\file   BehaviorDisplayPowerUp.h
\author Khaled Ishaque
\date   4-10-2023
\brief
        Functions for managing the behavior of a display mode signifier
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#pragma once

#include <glm/glm.hpp>

#include "Behavior.h"
#include "PowerUp.h"

#define NEW_PU_DISPLAY

class BehaviorDisplayPowerUp : public Behavior {
	public:

		/*!
		 * @brief:
		 * Constructor for the BehaviorDisplayPowerUp Class
		 * @param:
		 * None
		 * @return:
		 * Nothing
		 */
		BehaviorDisplayPowerUp();

		/*!
		 * @brief:
		 * Copy Constructor for the BehaviorDisplayPowerUp Class
		 * @param:
		 * None
		 * @return:
		 * Nothing
		 */
		BehaviorDisplayPowerUp(const BehaviorDisplayPowerUp &source);

		/*!
		 * @brief:
		 * update the behavior of the power up display
		 * @param:
		 * dt - calculated time passed per frame
		 * @return:
		 * Nothing
		 */
		BehaviorDisplayPowerUp *clone() const override;

		/*!
		 * @brief:
		 * clone a BehaviorDisplayPowerUp class
		 * @param:
		 * None
		 * @return:
		 * a copy of the behavior it was meant to clone
		 */
		void update(float dt);

#ifdef NEW_PU_DISPLAY

	private:

		//key: which powerup is the icon referring to
		/* KEY AS FOLLOWS:
		 * 1: Rapid Fire
		 * 2: More Bullets
		 * 3: Rapid Speed
		 */
		int key;

#else

		/*!
		 * @brief:
		 * set the color of the display when active
		 * @param:
		 * full - the vector containing the values to set the color vector
		 * @return:
		 * Nothing
		 */
		void setPowerUpColor(const glm::vec4 &full);

		/*!
		 * @brief:
		 * set the color of the display when inactive
		 * @param:
		 * d - the vector containing the values to set the color vector
		 * @return:
		 * Nothing
		 */
		void setDeadColor(const glm::vec4 &d);


		void setKey(const int k);
        
	private:

		//fullColor: color of the icon when active
		//dColor: color of icon when dead/inactive
		glm::vec4 fullColor, dColor;

		//key: which powerup is the icon referring to
		/* KEY AS FOLLOWS:
		 * 1: Rapid Fire
		 * 2: More Bullets
		 * 3: Rapid Speed
		 */
		int key;

#endif

};
