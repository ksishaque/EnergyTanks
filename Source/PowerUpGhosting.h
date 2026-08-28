/*!
\file PowerUpGhosting.h
\author Khaled S. Ishaque
\date 11-4-2022
\brief
	H file for Power Up Ghosting class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include "PowerUp.h"

class Ghosting : public PowerUp 
{
public:
    enum DisruptionValue
    {
        invalid = -1,
        up = 1,
        down = 2,
        left = 3,
        right = 4
    };
    Ghosting(float duration = 6.0f, DisruptionValue movementDisruptor = invalid);
    void initialize(BehaviorPlayer& behavior);
    void shutdown(BehaviorPlayer& behavior);
    //void setType(char dType);
    DisruptionValue getValue();
    bool isDisturbed();
    void setDisturbed(bool disturb = true);
    //const char getType();
private:
    //char type; //w for can't move up, s for can't rotate, b for can't move back, n for no ghosting
    DisruptionValue disruptorValue;
    bool disturbed;
};