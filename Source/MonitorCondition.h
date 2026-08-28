/*!
\file   MonitorCondition.h
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for creating and managing a conditional node for checking for multiple monitors
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class MonitorCondition;

#include "ConditionNode.h"

#define monitorCheck new MonitorCondition()

/*!
\class  MonitorCondition
\brief
        Nodes in an action list that check for multiple monitors
*/
class MonitorCondition : public ConditionNode{
	public:

		/*!
		\fn     MonitorCondition *clone() const
		\brief  See ActionNode.h
		*/
		MonitorCondition *clone() const;

	private:

		/*!
		\fn     bool condition() override
		\brief  See ConditionNode.h
		*/
		bool condition() override;

};