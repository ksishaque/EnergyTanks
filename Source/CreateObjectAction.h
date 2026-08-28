/*!
\file   CreateObjectAction.h
\author Kevin Shin
\date   3-16-2023
\brief
        Functions for creating and managing an action node for creating objects
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class CreateObjectAction;

#include <string>

#include "SequentialAction.h"

#define newObjAct(name, global) new CreateObjectAction(name, global)

/*!
\class  CreateObjectAction
\brief
        Nodes in an action list that creates an object
*/
class CreateObjectAction : public SequentialAction{
	public:

		/*!
		\fn     CreateObjectAction(const std::string &objectName, bool global)
		\param  objectName
		          Name of object to load
		\param  global
		          If the object needs to be parsed from the global folder
		\return Newly constructed object creation action
		\brief
		        This function constructs a new object creating node.
		*/
		CreateObjectAction(const std::string &objectName, bool global);

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
		\fn     CreateObjectAction *clone() const
		\brief  See ActionNode.h
		*/
		CreateObjectAction *clone() const;

	private:

		/*!
		\var   obj
		         Name of object to load
		*/
		std::string obj;

		/*!
		\var   global
		         If the object needs to be loaded from the global folder
		*/
		bool global;

};