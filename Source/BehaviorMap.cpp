/*!
\file   BehaviorMap.cpp
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   10-28-2022
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "BehaviorMap.h"

/*!
\fn     BehaviorMap()
\par    This function has no parameters.
\return The new behavior map
\brief
        This function constructs a behavior map.
*/
BehaviorMap::BehaviorMap() {
}

/*!
\fn     ~BehaviorMap()
\par    This function has no parameters.
\brief
        This function destructs a behavior map.
*/
BehaviorMap::~BehaviorMap() {
}

/*!
\fn     void update(float dt)
\param  dt
            The dt.
\brief
        This function updates.
*/
void BehaviorMap::update(float dt) {
}

Component* BehaviorMap::clone() const {
    BehaviorMap* clone = new BehaviorMap();
    return clone;
}
