/*!
\file   GameStateManager.cpp
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   10-13-2022
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "rapidjson/document.h"
#include "readFile.h"

#include "GameStateManager.h"
#include "GameStateBattle.h"
#include "Trace.h"

using rapidjson::Document;

GameStateManager* GameStateManager::instance = nullptr;

/*!
\fn     GameStateManager()
\brief  See GameStateManager.h
*/
GameStateManager::GameStateManager() :
    ISystem(sGSMan),
    previous(GsInvalid),
    current(GsInvalid),
    next(GsInvalid)
{
}

/*!
\fn     ~GameStateManager()
\brief  See GameStateManager.h
*/
GameStateManager::~GameStateManager()
{
}

GameStateManager* GameStateManager::getInstance()
{
    if (instance == nullptr) {
        instance = new GameStateManager();
    }
    return instance;
}

/*!
\fn     void GameStateManager::initialize()
\brief  See GameStateManager.h
*/
void GameStateManager::initialize()
{
    Trace::message("\t[GameStateManager]:initialize");
    if (isActive())
    {
        return;
    }
    ISystem::initialize();


    // Instantiate all game states and place in gsMap.
    // Read the game JSON file.
    const char* jsonData = readWholeFile("Data/Json/game.json");

    Document jsonDoc;
    jsonDoc.Parse(jsonData);

    if (!jsonDoc.IsObject() || !jsonDoc.HasMember("game states")) {
        return;
    }

    if (jsonDoc.HasMember("game states") && jsonDoc["game states"].IsArray()) {
        for (auto& element : jsonDoc["game states"].GetArray()) {
            if (element.IsObject()) {
                rapidjson::GenericObject<false, rapidjson::Value> gameState = element.GetObject();
                if (gameState.HasMember("name") && gameState.HasMember("data")) {
                    const char* gsName = gameState["name"].GetString();
                    const char* gsFilePath = gameState["data"].GetString();

                    if (gameStateCode(GsBattle).compare(gsName) == 0) {
                        gsMap[GsBattle] = new GameStateBattle(gsFilePath);
                    }
                }
            }
        }
    }

    // Set the initial game state to launch the game.
    next = GsInitial;
}


/*!
\fn     void GameStateManager::update()
\param  dt
          dt
\brief  See GameStateManager.h
*/
void GameStateManager::update(float dt)
{
    if (isGameStateChanging()) {
        Trace::message("\t[GameStateManager]:state change");

        // Shutdown current gamestate.
        if (current != GsInvalid && gsMap[current]) {
            gsMap[current]->shutdown();
        }

        if (isGameStateRestarting()) {
            next = current;
        }
        else {

            if (current != GsInvalid && gsMap[current]) {
                gsMap[current]->unload();
            }

            // Update the recorded states.
            previous = current;
            current = next;

            if (current != GsInvalid && gsMap[current]) {
                gsMap[current]->load();
            }
        }

        // Initialize the new game state.
        if (current != GsInvalid && gsMap[current]) {
            gsMap[current]->init();
        }
    }

    // Update the current game state.
    if (current != GsInvalid && gsMap[current]) {
        gsMap[current]->update(dt);
    }
}

/*!
\fn     bool isGameStateChanging()
\brief  See GameStateManager.h
*/
bool GameStateManager::isGameStateChanging() {
    return (current != next);
}

/*!
\fn     bool isGameStateRestarting()
\brief  See GameStateManager.h
*/
bool GameStateManager::isGameStateRestarting() {
    return next == GsRestart;
}

/*!
\fn     std::string gameStateCode(GameState gs)
\brief  See GameStateManager.h
*/
std::string GameStateManager::gameStateCode(GameState gs) {
    switch (gs)
    {
        case GsIntro:
            return "GsIntro";
        case GsBattle:
            return "GsBattle";
        case GsQuit:
            return "GsQuit";
        case GsRestart:
            return "GsRestart";
        default:
            return "GsInvalid";
    }
}

/*!
\fn     void GameStateManager::shutdown()
\brief  See GameStateManager.h
*/
void GameStateManager::shutdown()
{
    if (!isActive())
    {
        return;
    }
    ISystem::shutdown();

    for (auto iter : gsMap)
    {
        delete iter.second;
    }
    gsMap.clear();
}


