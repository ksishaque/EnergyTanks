/*!
\file   GameStateBattle.h
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   10-13-2022
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once
#include "IGameState.h"


class GameStateBattle : public IGameState {
    public:
        /*!
        \fn  GameStateBattle(const char* filePath)
        \param filePath
                 Path to the game state json file.
        \return Constructed game state
        \brief
                Constructor
        */
        GameStateBattle(const char* filePath);

        /*!
        \fn  ~GameStateBattle()
        \param none
        \brief
                Destructor
        */
        ~GameStateBattle();

        /*!
        \fn     void load()
        \par    This function has no parameters.
        \return Nothing
        \brief
                Load the resources associated with the game state.
        */
        void load() override;


        /*!
        \fn     void init()
        \par    This function has no parameters.
        \return Nothing
        \brief
                Initialize the memory associated with the game state.
        */
        void init() override;

        /*!
        \fn     void update(float dt)
        \param  dt
                  Change in time since the last game loop.
        \return Nothing
        \brief
                Update the game state, possibly switching to another game state.
        */
        void update(float dt) override;

        /*!
        \fn     void shutdown()
        \par    This function has no parameters.
        \return Nothing
        \brief
                Shutdown any memory associated with the game state.
        */
        void shutdown() override;

        /*!
        \fn     void unload()
        \par    This function has no parameters.
        \return Nothing
        \brief
                Unload the resources associated with the game state.
        */
        void unload() override;

        
};
