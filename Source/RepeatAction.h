/*!
\file   RepeatAction.h
\author Kevin Shin
\date   3-22-2023
\brief
        Functions for creating and managing an action node for repeating a set of sequential nodes
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class RepeatAction;

#include "ActionNode.h"

#define repeatAct(list) new RepeatAction(list)

class ActionList;

/*!
\class  RepeatAction
\brief
        Nodes in an action list that repeats a set of sequential nodes
*/
class RepeatAction : public ActionNode{
	public:

		/*!
		\fn     RepeatAction(ActionList *list)
		\param  list
		          List of nodes to repeat
		\return Newly constructed repeat action
		\brief
		        This function constructs a new repeat node.
		*/
		RepeatAction(ActionList *list);

		/*!
		\fn     ~RepeatAction()
		\par    This function has no parameters.
		\return Nothing
		\brief
		        This function destructs a repeat node.
		*/
		~RepeatAction();

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
		\fn     RepeatAction *clone() const
		\brief  See ActionNode.h
		*/
		RepeatAction *clone() const;

		/*!
		\fn     void repeat(float overtime)
		\param  overtime
		          Remaining time since last frame
		\brief  See ActionNode.h
		*/
		void repeat(float overtime);

	private:

		/*!
		\class  RepeatActionEnd
		\brief
		        Node marking the end of a repeated segment
		*/
		class RepeatActionEnd : public ActionNode{
			public:

				/*!
				\fn     RepeatActionEnd(RepeatAction *start)
				\param  start
				          Start of the repeated segment
				\return Newly constructed repeat action
				\brief
				        This function constructs a new repeat node.
				*/
				RepeatActionEnd(RepeatAction *start);

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
				\fn     RepeatAction *clone() const
				\brief  See ActionNode.h
				*/
				RepeatActionEnd *clone() const;

			private:

				/*!
				\var    start
				          Start or the repeated segment
				*/
				RepeatAction *start;

		};

		/*!
		\var    list
		          List of nodes to repeat
		*/
		ActionList *list;

		/*!
		\var    obj
		          Last object acted on, in case of a repeat
		*/
		GameObject *obj;

};