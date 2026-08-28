/*!
\file   ActionNode.h
\author Kevin Shin
\date   11-22-2022
\brief
        Functions for creating and maintaining a virtual node in an action list
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once

class GameObject;

/*!
\class  ActionNode
\brief
        Abstract class for nodes in an action list
*/
class ActionNode{
	public:

		/*!
		\fn     ActionNode()
		\par    This function has no parameters.
		\return Newly constructed action node
		\brief
		        This function constructs a new action node.
		*/
		ActionNode();

		/*!
		\fn     virtual ~ActionNode()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function destroys an action node.
		*/
		virtual ~ActionNode();

		/*!
		\fn     virtual void operator()(GameObject *object, float dt)
		\param  object
		          Game object calling the action
		\param  dt
		          Time since previous frame
		\return Nothing
		\brief
		        This function executes the action of the node and runs the next node.
		*/
		virtual void operator()(GameObject *object, float dt);

		/*!
		\fn     virtual ActionNode *clone() const
		\par    This function has no parameters.
		\return Copy of the action node
		\par    Note: THIS FUNCTION RETURNS DYNAMICALLY ALLOCATED MEMORY, WHICH MUST BE FREED!
		\brief
		        This function copies an action node.
		*/
		virtual ActionNode *clone() const = 0;

		/*!
		\fn     ActionNode &operator<<(ActionNode *next)
		\param  next
		          Node to set as `next`, expected to be dynamically allocated
		\return `this`, for chaining
		\brief
		          This function sets the next node in the action list
		*/
		ActionNode &operator<<(ActionNode &next);

		/*!
		\fn     void deleteAll()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function recursively destroys an action node.
		*/
		void deleteAll();

		/*!
		\fn     ActionNode *getNext() const
		\par    This function has no parameters.
		\return `next`
		\brief
		        This function accesses the next action node in the list.
		*/
		ActionNode *getNext() const;

	protected:

		/*!
		\fn     ActionNode *cloneNext() const
		\par    This function has no parameters.
		\return Copy of `next`
		\par    Note: THIS FUNCTION RETURNS DYNAMICALLY ALLOCATED MEMORY, WHICH MUST BE FREED!
		\brief
		        This function copies the next action node in the list.
		*/
		ActionNode *cloneNext() const;

	private:

		/*!
		\var    next
		          Next node in the action list
		\var    prev
		          Previous node's `next`
		*/
		ActionNode *next, **prev;

		/*!
		\class  ActionList
		\brief  See ActionList.h
		*/
		friend class ActionList;

};