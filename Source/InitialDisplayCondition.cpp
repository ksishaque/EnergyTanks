/*!
\file   InitialDisplayCondition.cpp
\author Kevin Shin
\date   11-22-2022
\brief
        Functions for creating and managing a conditional node for checking if a team has lost
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#include "TeamSystem.h"
#include "Trace.h"

#include "InitialDisplayCondition.h"

/*!
\fn     bool InitialDisplayCondition::condition()
\brief  See InitialDisplayCondition.h
*/
bool InitialDisplayCondition::condition(){
	return TeamSystem::getInstance() -> checkInitContDisplay();
}

/*!
\fn     InitialDisplayCondition *InitialDisplayCondition::clone() const
\brief  See InitialDisplayCondition.h
*/
InitialDisplayCondition *InitialDisplayCondition::clone() const{

	//	Variable: return value / clone of `this`
	InitialDisplayCondition *ans = new InitialDisplayCondition();

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}
