/*!
\file   IGameState.cpp
\author Benedict Yau (benedict.yau\@digipen.edu)
\date   10-13-2022
\par    Copyright © 2022 DigiPen, All rights reserved.
*/


#include "IGameState.h"
#include "Trace.h"


/*!
\fn     IGameState::IGameState(const char* filePath)
\brief  See IGameState.h
*/
IGameState::IGameState(const char* filePath)
{
    gameStateFilePath = std::string(filePath);

}
