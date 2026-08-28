/*!
\file PowerUpGhosting.cpp
\author Khaled S. Ishaque
\date 11-4-2022
\brief
    CPP file for Power Up Ghosting class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#include "PowerUpGhosting.h"
#include "Trace.h"

/*!
 * @brief:
 * Constructor for the Ghosting Class
 * @param:
 * duration - How long the power up will last
 * movementDisruptor - The button value that will be disturbed
 * @return:
 * Nothing
 */
Ghosting::Ghosting(float duration, DisruptionValue movementDisruptor) :
    PowerUp(PowerUp::ghosting, duration),
    disruptorValue(movementDisruptor),
    disturbed(false)
{
    Trace::message("Ghosting Constructor Called.");
    if (disruptorValue == invalid)
    {
        disruptorValue = up;
    }
    Trace::message("Ghosting Constructor Finished.");
}

/*!
 * @brief:
 * Initializes the Ghosting power up for the behavior
 * @param:
 * behavior - The current player behavior to alter
 * @return:
 * Nothing
 */
void Ghosting::initialize(BehaviorPlayer& behavior)
{
    Trace::message("Ghosting is Active.");
}

/*!
 * @brief:
 * Shuts down the Ghosting power up for the behavior
 * @param:
 * behavior - The current player behavior to alter
 * @return:
 * Nothing
 */
void Ghosting::shutdown(BehaviorPlayer& behavior)
{
    Trace::message("No More Ghosting.");
    disruptorValue = invalid;
}

/*!
 * @brief:
 * Gets the value of the power up's current disruption value 
 * @param:
 * None
 * @return:
 * disruptorValue - The current disruption value
 */
Ghosting::DisruptionValue Ghosting::getValue()
{
    return disruptorValue;
}

/*!
 * @brief:
 * Checks if the power up is currently disturbing a player
 * @param:
 * None
 * @return:
 * disturbed - The value (true or false) that determines if some player is being disturbed
 */
bool Ghosting::isDisturbed()
{
    return disturbed;
}

/*!
 * @brief:
 * Sets the disturbed checker of the power up to true or false (true = disturbing someone, false = not disturbing anyone)
 * @param:
 * disturb - The value that determines if a player is disturbed
 * @return:
 * Nothing
 */
void Ghosting::setDisturbed(bool disturb)
{
    //Trace::message("Is Setting disturbed: %s.",disturb ? "true" : "false");
    disturbed = disturb;
    if (disturbed == true)
    {
        Trace::message("Being Disturbed.");
    }
    else
    {
        Trace::message("Not Being Disturbed.");
    }
}