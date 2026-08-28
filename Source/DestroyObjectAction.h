/*!
\file   DestroyObjectAction.h
\author Kevin Shin
\date   4-4-2023
\brief
        Functions for creating and managing an action node for destroying objects
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class DestroyObjectAction;

#include <string>

#include "SequentialAction.h"

#define killObjAct(name) new DestroyObjectAction(name)

/*!
\class  DestroyObjectAction
\brief
        Nodes in an action list that destroys an object
*/
class DestroyObjectAction : public SequentialAction{
	public:

		/*!
		\fn     DestroyObjectAction(const std::string &objectName)
		\param  objectName
		          Name of object to destroy
		\return Newly constructed object destruction action
		\brief
		        This function constructs a new object destroying node.
		*/
		DestroyObjectAction(const std::string &objectName);

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
		\fn     DestroyObjectAction *clone() const
		\brief  See ActionNode.h
		*/
		DestroyObjectAction *clone() const;

	private:

		/*!
		\var   obj
		         Name of object to kill
		*/
		std::string obj;

};