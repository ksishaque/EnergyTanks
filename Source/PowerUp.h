/*!
\file PowerUp.h
\author Khaled S. Ishaque
\date 10-31-2022
\brief
    H file for Semi-Virtual PowerUp class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

//CLass definitions
class PowerUp;
class BehaviorPlayer;

class PowerUp
{
public:
	enum powerType {
		invalid,
		rapidFire, // fire bullets faster
		moreBullets, // fire extra bullets in 1 cycle
		rapidSpeed, // move fast
		burst, // fire bullets in a set
		pierce, // go through walls
		stealth, // "invisible" bullets
		random // sets to random power up
    };
    enum powerCategory {
        cInvalid,
        cTime,
        cAmmo
    };
    PowerUp(powerType type, powerCategory category, float duration, int ammo);
    powerType getType();
	powerCategory getCategory();
    void addDuration(float moreDur);
    void resetDuration(float originalDur);
    float getDuration();
	int getAmmo();
	void decreaseAmmo();
    virtual void initialize(BehaviorPlayer& behavior) {}
    virtual bool update(BehaviorPlayer& behavior, float dt);
    virtual void shutdown(BehaviorPlayer& behavior) {}
    virtual void moveEffect(BehaviorPlayer& behavior) {}
    virtual void shootEffect(BehaviorPlayer& behavior) {}
private:
    powerType type;
    powerCategory category;
    float duration;
	int ammo;
};