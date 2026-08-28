/*!
\file   ReloadAction.h
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for creating and managing an action node for reloading a set of sequential nodes
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class ReloadAction;

#include "ActionNode.h"

#define reloadAct(list) new ReloadAction(list)

class ActionList;

/*!
\class  ReloadAction
\brief
        Nodes in an action list that reloads a set of sequential nodes
*/
class ReloadAction : public ActionNode{
	public:

		/*!
		\fn     ReloadAction(ActionList *list)
		\param  list
		          List of nodes to reload
		\return Newly constructed reload action
		\brief
		        This function constructs a new reload node.
		*/
		ReloadAction(ActionList *list);

		/*!
		\fn     ~ReloadAction()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function destructs a reload node.
		*/
		~ReloadAction();

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
		\fn     ReloadAction *clone() const
		\brief  See ActionNode.h
		*/
		ReloadAction *clone() const;

	private:

		/*!
		\var    list
		          List of nodes to reload
		*/
		ActionList *list;

};