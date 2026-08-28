/*!
\file PowerUp.cpp
\author Khaled S. Ishaque
\date 10-31-2022
\brief
    CPP file for Semi-Virtual PowerUp class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#include "PowerUp.h"
#include "Trace.h"

/*!
 * @brief:
 * Constructor for PowerUp class
 * @param:
 * type - The type of power up that will be created
 * duration - The time the power up will be active for
 * @return:
 * Nothing
 */
PowerUp::PowerUp(powerType type, powerCategory category, float duration, int ammo) :
type(type),
category(category),
duration(duration),
ammo(ammo)
{
}

/*!
 * @brief:
 * Gets the type of power up made in the PowerUp class
 * @param:
 * None
 * @return:
 * type - The type of power up created
 */
PowerUp::powerType PowerUp::getType() {
    return type;
}

PowerUp::powerCategory PowerUp::getCategory() {
	return category;
}

/*!
 * @brief:
 * Adds more time to the power up's duration
 * @param:
 * moreDur - The amount of time to add to the power up's duration
 * @return:
 * Nothing
 */
void PowerUp::addDuration(float moreDur) {
#ifdef DEBUG_SYSTEM
    Trace::message("Adding %f to Duration.", moreDur);
#endif
    duration = duration + moreDur;
#ifdef DEBUG_SYSTEM
    Trace::message("New Duration: %f.", duration);
#endif
}

/*!
 * @brief:
 * Reset the timer of the power up's duration
 * @param:
 * originalDur - The duration of time to reset the timer with
 * @return:
 * Nothing
 */
void PowerUp::resetDuration(float originalDur) {
#ifdef DEBUG_SYSTEM
    Trace::message("Resetting Duration");
#endif
    duration = originalDur;
}

/*!
 * @brief:
 * Updates the timer of the power up and gives back the timer if it reaches the end
 * @param:
 * behavior - The player object that is affected by the power up
 * dt - The change in time
 * @return:
 * duration - The timer of the power up
 */
bool PowerUp::update(BehaviorPlayer& behavior, float dt) {
	if (category == cAmmo) {
#ifdef DEBUG_SYSTEM
		Trace::message("ammo count: %i", ammo);
#endif
		return ammo <= 0;
	}
	else if (category == cTime) {
		duration -= dt;
#ifdef DEBUG_SYSTEM
		Trace::message("Current duration of PowerUp: %f", duration);
#endif
		return duration <= 0;
	}
	/*duration -= dt;
	Trace::message("Current duration of PowerUp: %f", duration);
	return duration <= 0;*/
	
	//standard/default
	return false;
}

float PowerUp::getDuration() {
    return duration;
}

int PowerUp::getAmmo() {
	return ammo;
}

void PowerUp::decreaseAmmo() {
	--ammo;
}