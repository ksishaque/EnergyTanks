/*!
\file   LoadTextureAction.cpp
\author Kevin Shin
\date   |-|-2023
\brief
        Functions for creating and managing an action node for |
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "TextureManager.h"

#include "LoadTextureAction.h"

/*!
\fn     LoadTextureAction::LoadTextureAction(const std::string &name)
\param  name
          textureName
\brief  See LoadTextureAction.h
*/
LoadTextureAction::LoadTextureAction(const std::string &name) : textureName(name){}

/*!
\fn     void LoadTextureAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void LoadTextureAction::operator()(GameObject *obj, float dt){

	//	LoadTextureLoadTextureLoadTexture
	TextureManager::getTexture(textureName);

	//	Remove from list
	completed(obj, dt);

}

/*!
\fn     LoadTextureAction *LoadTextureAction::clone() const
\brief  See LoadTextureAction.h
*/
LoadTextureAction *LoadTextureAction::clone() const{

	//	Variable: return value / clone of `this`
	LoadTextureAction *ans = new LoadTextureAction(textureName);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}