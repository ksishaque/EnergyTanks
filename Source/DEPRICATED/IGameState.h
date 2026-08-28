/*!
\file   IGameState.h
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   10-13-2022
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once

#include <string>

class IGameState {
    public:

        /*!
        \fn     IGameState(const char* filePath)
        \param filePath
                 Path to the game state json file.
        \return Constructed game state
        \brief
                This function constructs a game state.
        */
        IGameState(const char* filePath);

        /*!
        \fn     virtual ~ISystem()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function deconstructs a game state.
        */
        virtual ~IGameState() {}

        /*!
        \fn     virtual void load()
        \par    This function has no parameters.
        \return Nothing
        \brief
                Load the resources associated with the game state.
        */
        virtual void load() {}

        /*!
        \fn     virtual void init()
        \par    This function has no parameters.
        \return Nothing
        \brief
                Initialize the memory associated with the game state.
        */
        virtual void init() {}

        /*!
        \fn     virtual void update(float dt)
        \param  dt
                  Change in time since the last game loop.
        \return Nothing
        \brief
                Update the game state, possibly switching to another game state.
        */
        virtual void update(float dt) {}

        /*!
        \fn     virtual void shutdown()
        \par    This function has no parameters.
        \return Nothing
        \brief
                Shutdown any memory associated with the game state.
        */
        virtual void shutdown() {}

        /*!
        \fn     virtual void unload()
        \par    This function has no parameters.
        \return Nothing
        \brief
                Unload the resources associated with the game state.
        */
        virtual void unload() {}

    protected:
        std::string gameStateFilePath;
};
