/*!
\file PowerUpVudoo.cpp
\author Khaled S. Ishaque
\date 11-11-2022
\brief
    CPP file for Power Up Vudoo class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#include <glfw/glfw3.h>

#include <random>

#include "PowerUpVudoo.h"
#include "Trace.h"

Vudoo::Vudoo(float duration) :
    PowerUp(PowerUp::powerType::vudoo, duration),
    origUp(0),
    origDown(0),
    origLeft(0),
    origRight(0),
    newUp(0),
    newDown(0),
    newLeft(0),
    newRight(0) {
    Trace::message("Vudoo Constructor Called.");
}

void Vudoo::initialize(BehaviorPlayer& behavior) {
    //get the og keys to remember to set back
    origUp = behavior.getUp();
    origDown = behavior.getDown();
    origLeft = behavior.getLeft();
    origRight = behavior.getRight();
    //change the behavior
    change(behavior);
    Trace::message("Vudoo Made.");
}

void Vudoo::shutdown(BehaviorPlayer& behavior) {
    //revert changes
    behavior.setUp(origUp);
    behavior.setDown(origDown);
    behavior.setLeft(origLeft);
    behavior.setRight(origRight);
    Trace::message("Vudoo Turned Off.");
}

void Vudoo::change(BehaviorPlayer& behavior) {
    //note for this or 2nd semester: find way to make it work correctly (looking at team currently makes it do it twice
    GameObject::Team currTeam = GameObject::Team::Neutral;
#if 0
    currTeam = behavior.getParent()->getTeam();
#endif
    //check the team that got the power up
    if (currTeam == GameObject::Team::Left) {
        newUp = GLFW_KEY_W;
        newDown = GLFW_KEY_S;
        newLeft = GLFW_KEY_A;
        newRight = GLFW_KEY_D;
        Trace::message("Player 1 Controls Player 2.");
    }
    else if (currTeam == GameObject::Team::Right) {
        newUp = GLFW_KEY_UP;
        newDown = GLFW_KEY_DOWN;
        newLeft = GLFW_KEY_LEFT;
        newRight = GLFW_KEY_RIGHT;
        Trace::message("Player 2 Controls Player 1.");
    }
    //can't decide
    else {
        int randInt = (rand() % 10) + 1;
        if (randInt < 5) {
            newUp = GLFW_KEY_W;
            newDown = GLFW_KEY_S;
            newLeft = GLFW_KEY_LEFT;
            newRight = GLFW_KEY_RIGHT;
            Trace::message("Combo 1.");
        }
        else if (randInt >= 5) {
            newUp = GLFW_KEY_UP;
            newDown = GLFW_KEY_DOWN;
            newLeft = GLFW_KEY_A;
            newRight = GLFW_KEY_D;
            Trace::message("Combo 2.");
        }
    }
    //set the new keys
    behavior.setUp(newUp);
    behavior.setDown(newDown);
    behavior.setLeft(newLeft);
    behavior.setRight(newRight);
    Trace::message("New Controls Set.");
}