/*!
\file   FunctionActionNode.h
\author Kevin Shin
\date   11-22-2022
\brief
        Functions for creating and maintaining a action nodes with functions
\par    Copyright © 2022 DigiPen, All rights reserved.
*/

#pragma once

#include "ActionNode.h"

typedef void (*ActionFunctionVoid)(void);
typedef void (*ActionFunctionObj)(GameObject &);
typedef void (*ActionFunctionObjPtr)(GameObject *);
typedef void (*ActionFunctionDt)(float);
typedef void (*ActionFunctionObjDt)(GameObject &, float);
typedef void (*ActionFunctionObjPtrDt)(GameObject *, float);

/*!
\class  ActionNode
\tparam Function
          Type of function used, which must be one of the `ActionFunction*` types.
\brief
        Abstract class for nodes in an action list
*/
template<typename Function> class FunctionActionNode : public ActionNode{
	public:

		/*!
		\fn     FunctionActionNode<Function>(Function function)
		\param  function
		          Function to run when the action is called
		\return Newly constructed function-based action node
		\brief
		        This function constructs a new function-based action node.
		*/
		FunctionActionNode(Function function);

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
		\fn     FunctionActionNode<Function> *clone() const
		\brief  See ActionNode.h
		*/
		FunctionActionNode<Function> *clone() const;

	private:

		/*!
		\var    fn
		          Function to run
		*/
		Function fn;

		/*!
		\fn     void run(GameObject *object, float dt)
		\param  object
		          object
		\param  dt
		          object
		\return Nothing
		\brief
		        This function runs the function inside the action node
		*/
		void run(GameObject *object, float dt);
};

#include "FunctionActionNodeTemplates.cpp"