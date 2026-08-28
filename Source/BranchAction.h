/*!
\file   BranchAction.h
\author Kevin Shin
\date   4-5-2023
\brief
        Functions for creating and managing an action node for branching sequential nodes
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class BranchAction;

#include "ActionNode.h"

#define branchAct(list) new BranchAction(list)

class ActionList;

/*!
\class  BranchAction
\brief
        Nodes in an action list that runs a separate branch of sequential nodes simultaneously
*/
class BranchAction : public ActionNode{
	public:

		/*!
		\fn     BranchAction(ActionList *list)
		\param  list
		          List of nodes to branch to
		\return Newly constructed branch action
		\brief
		        This function constructs a new branch node.
		*/
		BranchAction(ActionList *list);

		/*!
		\fn     ~BranchAction()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function destructs a branch node.
		*/
		~BranchAction();

		/*!
		\fn     void operator()(GameObject *object, float dt)
		\param  object
		          object
		\param  dt
		          dt
		\brief  See ActionNode.h
		*/
		void operator()(GameObject *object, float dt);

		/*!
		\fn     BranchAction *clone() const
		\brief  See ActionNode.h
		*/
		BranchAction *clone() const;

	private:

		/*!
		\var    list
		          List of nodes to reload
		*/
		ActionList *list;

};