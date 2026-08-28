/*!
\file PowerUpMoreBullets.h
\author Khaled S. Ishaque
\date 11-8-2022
\brief
    H file for Power Up MoreBullets class and functions in class
\par    Copyright © 2022 DigiPen, All rights reserved.
*/
#pragma once

#include "PowerUp.h"

class MoreBullets : public PowerUp
{
public:
    MoreBullets(float duration = 5.0f, int tier = 1);
    void addDuration(float moreDur = 5.0f);
    void increaseTier();
    void resetIncreaseCheck();
    int getTier();
private:
    int currTier;
    bool wasIncreased;
};