/*!
\file PowerUpRapidFire.cpp
\author Khaled S. Ishaque
\date 11-2-2022
\brief
    CPP file for Power Up RapidFire class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#include "BehaviorPlayer.h"
#include "PowerUpRapidFire.h"
#include "Trace.h"

/*!
 * @brief:
 * Initializes the Rapid Fire power up for the behavior
 * @param:
 * behavior - The current player behavior to alter
 * @return:
 * Nothing
 */
void RapidFire::initialize(BehaviorPlayer& behavior)
{
    //set the new cooldown of firing time
    float newCooldown = behavior.getMaxCooldown();
    newCooldown /= cdRatio;
    behavior.setMaxCooldown(newCooldown);
#ifdef DEBUG_SYSTEM
    Trace::message("RapidFire is Initialized");
#endif
}

/*!
 * @brief:
 * Shuts down the Ghosting power up for the behavior
 * @param:
 * behavior - The current player behavior to alter
 * @return:
 * Nothing
 */
void RapidFire::shutdown(BehaviorPlayer& behavior)
{
    //reset the cooldown back to original value
    float newCooldown = behavior.getMaxCooldown();
    newCooldown *= cdRatio;
    behavior.setMaxCooldown(newCooldown);
#ifdef DEBUG_SYSTEM
    Trace::message("RapidFire is Finished");
#endif
}

/*!
 * @brief:
 * Constructor for the RapidFire Class
 * @param:
 * ratio - The ratio for bullet fired/cooldown time
 * duration - The duration in which the power up is active
 * @return:
 * Nothing
 */
RapidFire::RapidFire(float ratio, float duration) :
    PowerUp(PowerUp::rapidFire, PowerUp::cTime, duration, 0),
    cdRatio(ratio)
{
#ifdef DEBUG_SYSTEM
    Trace::message("RapidFire Constructor Called");
#endif
}