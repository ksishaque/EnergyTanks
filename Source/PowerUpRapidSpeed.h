/*!
\file PowerUpRapidSpeed.h
\author Khaled S. Ishaque
\date 11-2-2022
\brief
    CPP file for Power Up RapidSpeed class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once

#include "PowerUp.h"

class RapidSpeed : public PowerUp
{
public:
    RapidSpeed(float ratio = 2, float duration = 5);
    //void shootEffect(BehaviorPlayer& behavior);
    void initialize(BehaviorPlayer& behavior);
    void shutdown(BehaviorPlayer& behavior);
private:
    float spdRatio;
};