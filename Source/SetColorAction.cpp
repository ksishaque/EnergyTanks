/*!
\file   SetColorAction.cpp
\author Kevin Shin
\date   3-17-2023
\brief
        Functions for creating and managing an action node for setting the color of an object.
\par    Copyright © 2023 DigiPen, All rights reserved.
*/

#include "GameObject.h"
#include "Sprite.h"

#include "SetColorAction.h"

/*!
\fn     SetColorAction::SetColorAction(const std::string &name)
\param  r
          red
\param  g
          green
\param  b
          blue
\param  a
          alpha
\brief  See SetColorAction.h
*/
SetColorAction::SetColorAction(float r, float g, float b, float a) : r(r), g(g), b(b), a(a){}

/*!
\fn     void SetColorAction::operator()(GameObject *obj, float dt)
\param  obj
          object
\param  dt
          dt
\brief  See ActionNode.h
*/
void SetColorAction::operator()(GameObject *obj, float dt){

	//	Check object
	if(obj == nullptr) return;

	//	Variable: Sprite of `obj`
	Sprite *spr = dynamic_cast<Sprite *>(obj -> get(ComponentTypeEnum::cSprite));

	//	Check `spr`
	if(spr == nullptr) return;

	//	Set color
	spr -> setColor(r, g, b, a);

	//	Set as completed
	completed(obj, dt);

}

/*!
\fn     SetColorAction *SetColorAction::clone() const
\brief  See ActionNode.h
*/
SetColorAction *SetColorAction::clone() const{

	//	Variable: return value / clone of `this`
	SetColorAction *ans = new SetColorAction(r, g, b, a);

	//	Set `next`
	ans -> operator<<(*cloneNext());

	//	Return
	return ans;

}