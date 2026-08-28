/*!
\file PowerUpManualBulletCtrl.h
\author Khaled S. Ishaque
\date 11-9-2022
\brief
    h file for ManualBulletCtrl class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include "PowerUp.h"

class ManualBulletCtrl : public PowerUp
{
public:
    ManualBulletCtrl(float duration = 5.0f, int ammo = 3);
    void initialize(BehaviorPlayer& behavior);
    void shutdown(BehaviorPlayer& behavior);
    void decreaseAmmo();
    void resetAmmo();
    void addAmmo(int moreAmmo);
private:
    int ammo;
};