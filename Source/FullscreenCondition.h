/*!
\file   FullscreenCondition.h
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for creating and managing a conditional node for checking the full screen state
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class FullscreenCondition;

#include "ConditionNode.h"

#define fullscreenCheck new FullscreenCondition()

/*!
\class  FullscreenCondition
\brief
        Nodes in an action list that check for the full screen state
*/
class FullscreenCondition : public ConditionNode{
	public:

		/*!
		\fn     FullscreenCondition *clone() const
		\brief  See ActionNode.h
		*/
		FullscreenCondition *clone() const;

	private:

		/*!
		\fn     bool condition() override
		\brief  See ConditionNode.h
		*/
		bool condition() override;

};