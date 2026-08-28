/*!
\file   FunctionActionNode.cpp
\author Kevin Shin
\date   11-22-2022
\brief
        Functions for creating and maintaining a action nodes with functions
\par    Copyright © 2022 DigiPen, All rights reserved.
\par    Note: These functions have been separated from FunctionActionNode.cpp and excluded from the build because it is a template function
*/

#pragma once

#include "FunctionActionNode.h"

/*!
\fn     void FunctionActionNode<ActionFunctionVoid>::run(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void FunctionActionNode<ActionFunctionVoid>::run(GameObject *obj, float dt){
	fn();
}

/*!
\fn     void FunctionActionNode<ActionFunctionObj>::run(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void FunctionActionNode<ActionFunctionObj>::run(GameObject *obj, float dt){
	if(obj) fn(*obj);
}

/*!
\fn     void FunctionActionNode<ActionFunctionObjPtr>::run(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void FunctionActionNode<ActionFunctionObjPtr>::run(GameObject *obj, float dt){
	fn(obj);
}

/*!
\fn     void FunctionActionNode<ActionFunctionDt>::run(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void FunctionActionNode<ActionFunctionDt>::run(GameObject *obj, float dt){
	fn(dt);
}

/*!
\fn     void FunctionActionNode<ActionFunctionObjDt>::run(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void FunctionActionNode<ActionFunctionObjDt>::run(GameObject *obj, float dt){
	if(obj) fn(*obj, dt);
}

/*!
\fn     void FunctionActionNode<ActionFunctionObjPtrDt>::run(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void FunctionActionNode<ActionFunctionObjPtrDt>::run(GameObject *obj, float dt){
	fn(obj, dt);
}