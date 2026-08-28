/*!
\file   AddToAction.cpp
\author Kevin Shin
\date   2-13-2023
\brief
        Functions for creating and managing an action node for setting a game object for future nodes
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "AddToAction.h"

/*!
\fn     template<typename T> AddToAction<T>::AddToAction(T &tar, const T &val)
\tparam T
          Type
\param  tar
          target
\param  val
          amount
\brief  See AddToAction.h
*/
template<typename T> AddToAction<T>::AddToAction(T &tar, T val) : ActionNode(), target(tar), amount(val){}

/*!
\fn     template<typename T> void AddToAction<T>::operator()(GameObject *obj, float dt)
\param  T
          Type
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
template<typename T> void AddToAction<T>::operator()(GameObject *obj, float dt){

	//	Add values
	target += amount;

	//	Recursive call to `next`
	ActionNode::operator()(obj, dt);

}
#include "Trace.h"
/*!
\fn     template<typename T> AddToAction<T> *AddToAction<T>::clone() const
\brief  See AddToAction.h
*/
template<typename T> AddToAction<T> *AddToAction<T>::clone() const{

	//Trace::message("Adding %f to %f", amount, target);

	//	Variable: return value / clone of `this`
	AddToAction<T> *ans = new AddToAction<T>(target, amount);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}

/*!
\fn     template<typename T> AddToAction<T> *addTo(T &tar, const T &val)
\tparam T
          Type
\param  tar
          target
\param  val
          amount
\brief  See AddToAction.h
*/
template<typename T> AddToAction<T> *addTo(T &tar, const T &val){
	return new AddToAction<T>(tar, val);
}