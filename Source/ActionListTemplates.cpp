/*!
\file   ActionListTemplates.cpp
\author Kevin Shin
\date   11-22-2022
\brief
        Template function for managing a list of actions
\par    Copyright © 2022 DigiPen, All rights reserved.
\par    Note: This function have been separated from ActionList.cpp and excluded from the build because it is a template function
*/

#pragma once

#include "ActionList.h"

/*!
\fn     template<typename F> void addFunction(F fn)
\tparam F
		  Function
\param  fn
          function
\brief  See ActionList.h
*/
template<typename F> void ActionList::addFunction(F fn){
	add(new FunctionActionNode<F>(fn));
}