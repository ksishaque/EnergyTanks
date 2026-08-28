/*!
\file   GameStateManager.h
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   10-13-2022
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once

#include <map>
#include "Engine.h"
#include "ISystem.h"
#include "IGameState.h"


/*!
\class  GameStateManager
\brief
        This class stores multiple game states and tracks the current game state.
*/
class GameStateManager : public ISystem {
    public:
        enum GameState {
            /* Special Game States */
            GsQuit = -3,
            GsRestart = -2,
            GsInvalid = -1,

            /* Normal Game States: */
            GsIntro,
            GsBattle,

            /* Bookkeeping States: */
            GsNum,
            GsLast = GsNum - 1,

            /* Specify the initial game state */
            GsInitial = GsBattle,
        };


    public:
        /**
         * This function accesses the singleton instance of the game state manager system, creating it if needed.
         *
         * \return Singleton instance of the game state manager system
        */
        static GameStateManager* getInstance();

        /*!
        \fn     void initialize()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function initializes the game state manager.
        */
        void initialize() override;

        /*!
        \fn     void update(float dt)
        \param  dt
                  time since previous frame
        \return Nothing
        \brief
                This function updates every object in the object manager, then starts the collision queue.
        */
        void update(float dt) override;

        /*!
        \fn     void shutdown()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function shuts down the object manager.
        */
        void shutdown() override;

    private:
        /*!
        \fn     GameStateManager()
        \par    This function has no parameters
        \return Constructed game state manager
        \brief
                This function constructs a game state manager.
        */
        GameStateManager();

        /*!
        \fn     ~GameStateManager()
        \par    This function has no parameters.
        \return Nothing
        \brief
                This function destructs a game state manager.
        */
        ~GameStateManager();

        /*!
        \fn     bool isGameStateChanging()
        \par    This function has no parameters.
        \return boolean
        \brief
                This function checks if the game state is changing.
        */
        bool isGameStateChanging();

        /*!
        \fn     bool isGameStateRestarting()
        \par    This function has no parameters.
        \return boolean
        \brief
                This function checks if the game state is restarting.
        */
        bool isGameStateRestarting();

        /*!
        \fn     std::string gameStateCode(GameState gs)
        \par    gs
                  The GameState enum
        \return std::string
        \brief
                This function converts GameState enum to std::string equivalent.
        */
        std::string gameStateCode(GameState gs);


    private:
        static GameStateManager* instance;

        GameState previous;
        GameState current;
        GameState next;

        // Mapping of GameState to IGameState *.
        std::map<GameState, IGameState*> gsMap;
};
