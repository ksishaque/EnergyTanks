/*!
\file   AddToAction.h
\author Kevin Shin
\date   2-13-2023
\brief
        Functions for creating and managing an action node for setting a game object for future nodes
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

#include "ActionNode.h"

/*!
\class  AddToAction
\tparam Type
          Type of values to add
\brief
        Nodes in an action list that adds a value to a reference
*/
template<typename Type> class AddToAction : public ActionNode{
	public:

		/*!
		\fn     AddToAction(Type &target, const Type &amount)
		\param  target
		          Value to add to
		\param  amount
		          Value to add
		\return Newly constructed object action
		\brief
		        This function constructs a new object node.
		*/
		AddToAction(Type &target, Type amount);

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
		\fn     AddToAction *clone() const
		\brief  See ActionNode.h
		*/
		AddToAction *clone() const;

	private:

		/*!
		\var    target
		          Value to add to
		*/
		Type &target;

		/*!
		\var    amount
		          Value to add
		*/
		Type amount;

};

/*!
\fn     template<typename Type> AddToAction<Type> addTo(Type &target, const Type &amount)
\param  target
          Value to add to
\param  amount
          Value to add
\return Newly constructed object action
\brief
        This function constructs a new object node.
*/
template<typename Type> AddToAction<Type> *addTo(Type &target, const Type &amount);

#include "AddToAction.cpp"