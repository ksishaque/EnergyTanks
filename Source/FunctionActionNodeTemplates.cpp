/*!
\file   FunctionActionNodeTemplates.cpp
\author Kevin Shin
\date   11-22-2022
\brief
        Functions for creating and maintaining a virtual node in an action list
\par    Copyright © 2022 DigiPen, All rights reserved.
\par    Due to template functions, this file is excluded from the build.
*/

#pragma once

#include "FunctionActionNode.h"

/*!
\fn     template<typename F> void FunctionActionNode<F>::operator()(GameObject *obj, float dt)
\tparam F
          Function
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
template<typename F> void FunctionActionNode<F>::operator()(GameObject *obj, float dt){
	
	//	Run `fn`
	run(obj, dt);

	//	Run next
	ActionNode::operator()(obj, dt);
}

/*!
\fn     template<typename F> FunctionActionNode<F> *FunctionActionNode<F>::clone() const
\tparam F
          Function
\brief  See ActionNode.h
*/
template<typename F> FunctionActionNode<F> *FunctionActionNode<F>::clone() const{

	//	Variable: return value / clone of `this`
	FunctionActionNode<F> *ans = new FunctionActionNode<F>(fn);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;
}

/*!
\fn     template<typename F> FunctionActionNode<F>::FunctionActionNode<F>(F fn)
\tparam F
          Function
\param  fn
          function
\brief  See ActionNode.h
*/
template<typename F> FunctionActionNode<F>::FunctionActionNode(F fn) : ActionNode(), fn(fn){}