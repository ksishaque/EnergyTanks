/*!
\file   LoadTextureAction.h
\author Kevin Shin
\date   3-13-2023
\brief
        Functions for creating and managing an action node for loading texture ahead of time
\par    Copyright © 2023 DigiPen, All rights reserved.
*/
#pragma once

class LoadTextureAction;

#include <string>

#include "SequentialAction.h"

#define loadTextureAct(name) new LoadTextureAction(name)

/*!
\class  LoadTextureAction
\brief
        Nodes in an action list that loads a texture
*/
class LoadTextureAction : public SequentialAction{
	public:

		/*!
		\fn     LoadTextureAction(const std::string &textureName)
		\param  
		\return Newly constructed texture loading action
		\brief
		        This function constructs a new texture loading node.
		*/
		LoadTextureAction(const std::string &textureName);

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
		\fn     LoadTextureAction *clone() const
		\brief  See ActionNode.h
		*/
		LoadTextureAction *clone() const;

	private:

		/*!
		\var    textureName
		*/
		std::string textureName;

};