/*!
\file PowerUpMoreBullets.cpp
\author Khaled S. Ishaque
\date 11-8-2022
\brief
    CPP file for Power Up MoreBullets class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#include "PowerUpMoreBullets.h"
#include "BehaviorPlayer.h"
#include "Trace.h"

/*!
 * @brief:
 * Constructor for the MoreBullets Class
 * @param:
 * duration - How long the power up will last
 * tier - the tier of this created power up
 * @return:
 * Nothing
 */
MoreBullets::MoreBullets(float duration, int tier) :
    PowerUp(PowerUp::moreBullets, PowerUp::cTime, duration, 0),
    currTier(tier),
    wasIncreased(false)
{
}

/*!
 * @brief:
 * Increases the tier of the current MoreBullets power up
 * @param:
 * None
 * @return:
 * Nothing
 */
void MoreBullets::increaseTier()
{
    if (!wasIncreased) 
    {
        
        if (currTier < 3)
        {
#ifdef DEBUG_SYSTEM
            Trace::message("Tier Increaded by 1.");
#endif
            ++currTier;
        }
        
        //++currTier;
#ifdef DEBUG_SYSTEM
        Trace::message("Current Tier: %i", currTier);
#endif
        resetDuration(5);
        wasIncreased = true;
    }
}

/*!
 * @brief:
 * Adds more time to the duration of the power up
 * @param:
 * moreDur - The amount of time to add to the duration
 * @return:
 * Nothing
 */
void MoreBullets::addDuration(float moreDur)
{
    PowerUp::addDuration(moreDur);
}

/*!
 * @brief:
 * Reset the increase checker if the power up was increased
 * @param:
 * None
 * @return:
 * Nothing
 */
void MoreBullets::resetIncreaseCheck()
{
    wasIncreased = false;
#ifdef DEBUG_SYSTEM
    Trace::message("Increase Checker Resetted.");
#endif
}

/*!
 * @brief:
 * Gets the current tier of the power up
 * @param:
 * None
 * @return:
 * currTier - The power up's current tier
 */
int MoreBullets::getTier()
{
    return currTier;
}