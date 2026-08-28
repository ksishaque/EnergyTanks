/*!
\file   GameStateBattle.cpp
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   10-13-2022
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "rapidjson/document.h"
#include "readFile.h"
#include "GameStateBattle.h"
#include "Trace.h"

using rapidjson::Document;

/*!
\fn     GameStateBattle::GameStateBattle(const char* filePath)
\brief  See GameStateBattle.h
*/
GameStateBattle::GameStateBattle(const char* filePath) : 
    IGameState(filePath)
{
    
}

/*!
\fn     GameStateBattle::~GameStateBattle()
\brief  See GameStateBattle.h
*/
GameStateBattle::~GameStateBattle()
{
}


void GameStateBattle::load()
{
    Trace::message("\t[GameStateBattle]:load");

    Document jsonDoc;


    // Instantiate all game states and place in gsMap.
    // Read the game JSON file.
    const char* jsonData = readWholeFile(gameStateFilePath.c_str());
    jsonDoc.Parse(jsonData);

    if (!jsonDoc.IsObject() || !jsonDoc.HasMember("id")) {
        return;
    }


    if (jsonDoc.IsObject()) {
        if (jsonDoc.HasMember("game objects") && jsonDoc["game objects"].IsArray()) {
            for (auto& element : jsonDoc["game objects"].GetArray()) {
                if (element.IsObject()) {
                    rapidjson::GenericObject<false, rapidjson::Value> gameObject = element.GetObject();
                    if (gameObject.HasMember("name") && gameObject.HasMember("data")) {
                        const char* goName = gameObject["name"].GetString();
                        const char* goFilePath = gameObject["data"].GetString();
                        Trace::message(goName);
                        Trace::message(goFilePath);

                    }
                }
            }
        }
    }
}

/*!
\fn     GameStateBattle::~GameStateBattle()
\brief  See GameStateBattle.h
*/
void GameStateBattle::init()
{
    Trace::message("\t[GameStateBattle]:init");
}

/*!
\fn     GameStateBattle::~GameStateBattle()
\brief  See GameStateBattle.h
*/
void GameStateBattle::update(float dt)
{
    Trace::message("\t[GameStateBattle]:update");
}

/*!
\fn     GameStateBattle::~GameStateBattle()
\brief  See GameStateBattle.h
*/
void GameStateBattle::shutdown()
{
    Trace::message("\t[GameStateBattle]:shutdown");
}

/*!
\fn     GameStateBattle::~GameStateBattle()
\brief  See GameStateBattle.h
*/
void GameStateBattle::unload()
{
    Trace::message("\t[GameStateBattle]:unload");
}