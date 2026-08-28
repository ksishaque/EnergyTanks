/*!
\file PowerUpConfuse.h
\author Khaled S. Ishaque
\date 11-11-2022
\brief
    H file for Power Up Confuse class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include "PowerUp.h"

class Confuse : public PowerUp
{
public:
    Confuse(float duration = 5.0f);
    void initialize(BehaviorPlayer& behavior);
    void shutdown(BehaviorPlayer& behavior);
    void change(BehaviorPlayer& behavior);
private:
    int origUp, origDown, origLeft, origRight;
    int newUp, newDown, newLeft, newRight;
};