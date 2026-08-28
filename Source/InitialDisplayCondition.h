/*!
\file   InitialDisplayCondition.h
\author Kevin Shin
\date   4-7-2022
\brief
        Functions for creating and managing a conditional node for checking if the initial controls display is needed
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class InitialDisplayCondition;

#include "ConditionNode.h"
#include "GameObject.h"

#define initialDisplayCheck new InitialDisplayCondition()

/*!
\class  InitialDisplayCondition
\brief
        Action nodes that only continues in the list when the initial team display has not been displayed
*/
class InitialDisplayCondition : public ConditionNode{
	public:

		/*!
		\fn     InitialDisplayCondition *clone() const
		\brief  See ConditionNode.h
		*/
		InitialDisplayCondition *clone() const;

	private:

		/*!
		\fn     bool condition()
		\brief  See ConditionNode.h
		*/
		bool condition();
};