/*!
\file PowerUpRapidSpeed.cpp
\author Khaled S. Ishaque
\date 11-2-2022
\brief
    CPP file for Power Up RapidSpeed class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "BehaviorPlayer.h"
#include "PowerUpRapidSpeed.h"
#include "Trace.h"

/*!
 * @brief:
 * Constructor for the RapidSpeed Class
 * @param:
 * ratio - The new speed for the players that have the power up
 * duration - How long the power up will last
 * @return:
 * Nothing
 */
RapidSpeed::RapidSpeed(float ratio, float duration) :
    PowerUp(PowerUp::rapidSpeed, PowerUp::cTime, duration, 0),
    spdRatio(ratio)
{
#ifdef DEBUG_SYSTEM
    Trace::message("RapidSpeed Constructor Called");
#endif
}

/*!
 * @brief:
 * Initializes the RapidSpeed power up and increases the speed of the player
 * @param:
 * behavior - The current player behavior to alter
 * @return:
 * Nothing
 */
void RapidSpeed::initialize(BehaviorPlayer& behavior) {
    float newSpeed = behavior.getFore(), newBack = behavior.getBack();
    newSpeed *= spdRatio;
	newBack *= spdRatio;
    behavior.setFore(newSpeed);
	behavior.setBack(newBack);
#ifdef DEBUG_SYSTEM
    Trace::message("RapidSpeed has been Made.");
#endif
}

/*!
 * @brief:
 * Shuts down the rapid speed power up and increases the speed of the player
 * @param:
 * behavior - The current player behavior to revert to normal
 * @return:
 * Nothing
 */
void RapidSpeed::shutdown(BehaviorPlayer& behavior) {
    float newSpeed = behavior.getFore(), newBack = behavior.getBack();
    newSpeed /= spdRatio;
	newBack /= spdRatio;
    behavior.setFore(newSpeed);
	behavior.setBack(newBack);
#ifdef DEBUG_SYSTEM
    Trace::message("RapidSpeed is Finished.");
#endif
}