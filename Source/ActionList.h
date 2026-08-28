/*!
\file   ActionList.h
\author Kevin Shin
\date   11-22-2022
\brief
        Functions for creating and managing a list of actions
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once

class ActionList;

#include "Component.h"
#include "FunctionActionNode.h"

class ActionNode;

/*!
\class  ActionList
\brief
        List of actions to be preformed by a game object
*/
class ActionList : public Component{
	public:

		/*!
		\fn     ActionList()
		\par    This function takes no parameters.
		\return Constructed action list
		\brief
		        This function constructs a new action list.
		*/
		ActionList();

		/*!
		\fn     ActionList(const ActionList &source)
		\param  source
		          Action list to copy
		\return Constructed behavior
		\brief
		        This function constructs a new action list by copying an existing list.
		*/
		ActionList(const ActionList &source);

		/*!
		\fn     ~ActionList()
		\par    This function takes no parameters.
		\return Nothing
		\brief
		        This function deconstructs an action list.
		*/
		~ActionList();

		/*!
		\fn     void update(float dt)
		\param  dt
		          dt
		\brief  See Component.h
		*/
		void update(float dt);

		/*!
		\fn     void update(float dt, GameObject obj)
		\param  dt
		          Time since previous frame
		\param  object
		          Object to run the action list on
		\return Nothing
		\brief
		        This function updates the action list on a given object
		*/
		void update(float dt, GameObject *object);

		/*!
		\fn     ActionList *clone() const
		\brief  See Component.h
		*/
		ActionList *clone() const;

		/*!
		\fn     void add(ActionNode *node)
		\param  node
		          Action node to add to the list, assumed to be dynamically allocated
		\return Nothing
		\brief
		        This function adds an action node to the action list.
		*/
		void add(ActionNode *node);

		/*!
		\fn     void add(const ActionList *list)
		\param  list
		          Action list to add to the list
		\return Nothing
		\brief
		        This function adds a copy of a list of action nodes to the action list.
		*/
		void add(const ActionList *list);

		/*!
		\fn     ActionNode *get()
		\par    This function has no parameters
		\return `list`
		\brief
		        This function accesses the action nodes in the action list.
		*/
		ActionNode *get();

		/*!
		\fn     const ActionNode *get() const
		\par    This function has no parameters
		\return `list`
		\brief
		        This function accesses the action nodes in the action list.
		*/
		const ActionNode *get() const;

		/*!
		\fn     template<typename Function> void addFunction(Function function)
		\tparam Function
		          Type of function used, which must be one of the `ActionFunction*` types in FunctionActionNode.h.
		\param  function
		          Function to add to the list
		\return Nothing
		\brief
		        This function adds a function to the action list.
		*/
		template<typename Function> void addFunction(Function function);

		/*!
		\fn     void clear()
		\par    This function has no parameters
		\return Nothing
		\brief
		        This function clears all actions in the action list.
		*/
		void clear();

	private:

		/*!
		\var    list
		          Head node of linked list of action nodes to run
		*/
		ActionNode *list;

};

#include "ActionListTemplates.cpp"