/*!
\file PowerUpRapidFire.h
\author Khaled S. Ishaque
\date 11-2-2022
\brief
    H file for Power Up RapidFire class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include "PowerUp.h"

class RapidFire : public PowerUp
{
public:
    RapidFire(float ratio = 3, float duration = 5);
    //void shootEffect(BehaviorPlayer& behavior);
    void initialize(BehaviorPlayer& behavior);
    void shutdown(BehaviorPlayer& behavior);
private:
    float cdRatio;
};