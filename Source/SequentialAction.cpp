/*!
\file   SequentialAction.cpp
\author Kevin Shin
\date   |-|-2023
\brief
        Functions for creating and managing an action node for |
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "SequentialAction.h"

/*!
\fn     void SequentialAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          overtime
\brief  See ActionNode.h
*/
void SequentialAction::completed(GameObject *obj, float dt){

	//	Variable: Next node in list
	ActionNode *next = getNext();

	//	Delete `this`
	delete this;

	//	Recursive call to next
	if(next) next -> operator()(obj, dt);

}

/*!
\fn     SequentialAction::SequentialAction()
\brief  See SequentialAction.h
*/
SequentialAction::SequentialAction() : ActionNode(){}