/*!
\file PowerUpManualBulletCtrl.cpp
\author Khaled S. Ishaque
\date 11-9-2022
\brief
	CPP file for ManualBulletCtrl class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#include "PowerUpManualBulletCtrl.h"
#include "Trace.h"

ManualBulletCtrl::ManualBulletCtrl(float duration, int ammo) :
    PowerUp(PowerUp::powerType::ManualBullet, duration),
    ammo(ammo)
{
    Trace::message("ManualBulletCtrl Ctor Called.");
}

void ManualBulletCtrl::initialize(BehaviorPlayer& behavior)
{
    Trace::message("Initializing Manual Bullet Control...");
    try
    {
        if (&behavior != nullptr)
        {
            Trace::message("Manual Bullet Control: Confirmed.");
        }
        else
        {
            throw -1;
        }
    }
    catch (int error)
    {
        if (error == -1)
        {
            Trace::message("Error: Manual Bullet Control Blocked.");
        }
    }
}

void ManualBulletCtrl::shutdown(BehaviorPlayer& behavior)
{
    Trace::message("Shutting Down: Manual Bullet Control.");
    try
    {
        if (&behavior != nullptr)
        {
            Trace::message("Manual Bullet Control: OFF.");
        }
        else
            throw -1;
    }
    catch (int error)
    {
        if (error == -1)
        {
            Trace::message("Error: Unable to turn off Manual Bullet Control.");
        }
    }
}

void ManualBulletCtrl::decreaseAmmo()
{
    --ammo;
    Trace::message("Bullets left: %i.", ammo);
}

void ManualBulletCtrl::resetAmmo()
{
    ammo = 3;
    Trace::message("Bullet Count: Reset.");
}

void ManualBulletCtrl::addAmmo(int moreAmmo)
{
    ammo += moreAmmo;
    Trace::message("Bullet Count: %i", ammo);
}