/*!
\file   LockStateAction.h
\author Kevin Shin
\date   4-7-2023
\brief
        Functions for creating and managing an action node for locking the gamestate
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class LockStateAction;

#include "ActionNode.h"

#define lockGamestate(lock) new LockStateAction(lock)

/*!
\class  LockStateAction
\brief
        Nodes in an action list that locks the gamestate
*/
class LockStateAction : public ActionNode{
	public:

		/*!
		\fn     LockStateAction(bool lock)
		\param  lock
		          If the gamestate should be locked
		\return Newly constructed lockstate action
		\brief
		        This function constructs a new lockstate node.
		*/
		LockStateAction(bool lock);

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
		\fn     LockStateAction *clone() const
		\brief  See ActionNode.h
		*/
		LockStateAction *clone() const;

	private:

		/*!
		\var    lock
		          If the gamestate should be locked
		*/
		bool lock;

};