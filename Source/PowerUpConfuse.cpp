/*!
\file PowerUpConfuse.cpp
\author Khaled S. Ishaque
\date 11-11-2022
\brief
    H file for Power Up Confuse class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#include <random>

#include "PowerUpConfuse.h"
#include "Trace.h"

Confuse::Confuse(float duration) :
    PowerUp(PowerUp::powerType::confuse, duration),
    origUp(0),
    origDown(0),
    origLeft(0),
    origRight(0),
    newUp(0),
    newDown(0),
    newLeft(0),
    newRight(0) {
    Trace::message("Confuse Constructor Called.");
}

void Confuse::initialize(BehaviorPlayer& behavior) {

    //get the og keys to remember to set back
    origUp = behavior.getUp();
    origDown = behavior.getDown();
    origLeft = behavior.getLeft();
    origRight = behavior.getRight();
    //change the behavior
    change(behavior);
    Trace::message("Confusion Made.");
}

void Confuse::shutdown(BehaviorPlayer& behavior) {
    //revert changes
    behavior.setUp(origUp);
    behavior.setDown(origDown);
    behavior.setLeft(origLeft);
    behavior.setRight(origRight);
    Trace::message("Confusion Turned Off.");
}

void Confuse::change(BehaviorPlayer& behavior)
{
    int randInt = rand() % 10;
    //set different kind of combos
    if (randInt <= 2)
    {
        newUp = origDown;
        newDown = origUp;
        newLeft = origRight;
        newRight = origLeft;
        Trace::message("Combo 1.");
    }
    else if (randInt > 2 && randInt <= 5)
    {
        newUp = origLeft;
        newDown = origRight;
        newLeft = origUp;
        newRight = origDown;
        Trace::message("Combo 2.");
    }
    else if (randInt > 5 && randInt <= 7)
    {
        newUp = origRight;
        newDown = origLeft;
        newLeft = origDown;
        newRight = origUp;
        Trace::message("Combo 3.");
    }
    else if (randInt > 7 && randInt <= 10)
    {
        newUp = origDown;
        newDown = origRight;
        newLeft = origUp;
        newRight = origLeft;
        Trace::message("Combo 4.");
    }
    //set the confusion key combo
    behavior.setUp(newUp);
    behavior.setDown(newDown);
    behavior.setLeft(newLeft);
    behavior.setRight(newRight);
}