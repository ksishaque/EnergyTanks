/*!
\file   BehaviorMap.h
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   10-28-2022
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once

#include  "Behavior.h"

class BehaviorMap : public Behavior {
    public:
        /*!
        \fn     BehaviorMap()
        \par    This function has no parameters.
        \return The new behavior map
        \brief
                This function constructs a behavior map.
        */
        BehaviorMap();

        /*!
        \fn     ~BehaviorMap()
        \par    This function has no parameters.
        \brief
                This function destructs a behavior map.
        */
        ~BehaviorMap();

        /*!
        \fn     void update(float dt)
        \param  dt
                    The dt (the change in time)
        \brief
                This function updates.
        */
        void update(float dt);

        /*!
        \fn Component* clone() const
        \par This function has no parameters.
        \brief
                This function clones a behavior map.
        */
        Component* clone() const override;
};
